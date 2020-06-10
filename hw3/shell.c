#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include "tokenizer.h"

/* Convenience macro to silence compiler warnings about unused function parameters. */
#define unused __attribute__((unused))

/* Whether the shell is connected to an actual terminal or not. */
bool shell_is_interactive;

/* File descriptor for the shell input */
int shell_terminal;

/* Terminal mode settings for the shell */
struct termios shell_tmodes;

/* Process group id for the shell */
pid_t shell_pgid;

/* The linux environment PATH variable */
struct tokens *PATH;

int cmd_exit(struct tokens *tokens);
int cmd_help(struct tokens *tokens);
int cmd_pwd(struct tokens *tokens);
int cmd_cd(struct tokens *tokens);

/* Built-in command functions take token array (see parse.h) and return int */
typedef int cmd_fun_t(struct tokens *tokens);

/* Built-in command struct and lookup table */
typedef struct fun_desc {
  cmd_fun_t *fun;
  char *cmd;
  char *doc;
} fun_desc_t;

fun_desc_t cmd_table[] = {
  {cmd_help, "?", "show this help menu"},
  {cmd_exit, "exit", "exit the command shell"},
  {cmd_pwd, "pwd", "show the current working directory"},
  {cmd_cd, "cd", "change the current working directory"},
};

int pipefd[2];

/* Prints a helpful description for the given command */
int cmd_help(unused struct tokens *tokens) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    printf("%s - %s\n", cmd_table[i].cmd, cmd_table[i].doc);
  return 1;
}

/* Exits this shell */
int cmd_exit(unused struct tokens *tokens) {
  exit(0);
}

int cmd_pwd(struct tokens *tokens) {
  char dir[256];
  char *error = getcwd(dir, 256);
  if (error != NULL) {
    printf("%s\n", dir);
  } else {
    printf("Error, the path is too long\n");
  }
  return 1;
}

int cmd_cd(struct tokens *tokens) {
  char* path = tokens_get_token(tokens, 1);
  int result = chdir(path);
  if (result == -1) {
    printf ("%s is not found\n", path);
    return -1;
  }
  return 1;
}

/* Looks up the built-in command, if it exists. */
int lookup(char cmd[]) {
  for (unsigned int i = 0; i < sizeof(cmd_table) / sizeof(fun_desc_t); i++)
    if (cmd && (strcmp(cmd_table[i].cmd, cmd) == 0))
      return i;
  return -1;
}

/* Intialization procedures for this shell */
void init_shell() {
  /* Our shell is connected to standard input. */
  shell_terminal = STDIN_FILENO;

  /* Check if we are running interactively */
  shell_is_interactive = isatty(shell_terminal);

  /* Load the PATH variable */
  PATH = tokenize(getenv("PATH"), ':');

  if (shell_is_interactive) {
    /* If the shell is not currently in the foreground, we must pause the shell until it becomes a
     * foreground process. We use SIGTTIN to pause the shell. When the shell gets moved to the
     * foreground, we'll receive a SIGCONT. */
    while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
      kill(-shell_pgid, SIGTTIN);

    /* Saves the shell's process id */
    shell_pgid = getpid();

    /* Take control of the terminal */
    tcsetpgrp(shell_terminal, shell_pgid);

    /* Save the current termios to a variable, so it can be restored later. */
    tcgetattr(shell_terminal, &shell_tmodes);
  }
}

int resolve_path(const char* path, char* resolved_path) {
  int n = tokens_get_length(PATH);
  char temp[1024];
  for (int i = 0; i < n; i++) {
    char* dir = tokens_get_token(PATH, i);
    int len = strlen(dir);
    strcpy(temp, dir);
    temp[len] = '/', temp [len+1] = '\0';
    strcat(temp, path);
    if (access(temp, F_OK) != -1) {
      strcpy(resolved_path, temp);
      return 0;
    }
  }
  return -1;
}

void redirect(struct tokens *tokens) {
  int n = tokens_get_length(tokens);
  for (int i = 0; i < n; i++) {
    char* token = tokens_get_token(tokens, i);
    if (strcmp(token, "<") == 0) {
      char* input = tokens_get_token(tokens, i+1);
      int fd = open(input, O_RDONLY, 0);
      if (fd == -1) {
        printf ("Input file %s is not found or does not have permission to read.\n", input);
        exit(-1);
      }
      dup2(fd, STDIN_FILENO);
      close(fd);

    } else if (strcmp(token, ">") == 0) {
        char* output = tokens_get_token(tokens, i+1);
        int fd = creat(output, 0644);
        if (fd == -1) {
          printf ("Output file %s is not found or does not have permission to read.\n", output);
          exit(-1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
  }
}

int count_num_command(struct tokens *tokens) {
  int n = tokens_get_length(tokens);
  int cnt = 1;
  for (int i = 0; i < n; i++) {
    if (strcmp(tokens_get_token(tokens, i), "|") == 0) cnt++;
  }
  return cnt;
}

void execute_user_program(struct tokens *tokens, int in, int out) {
  int pid = fork();
  if (pid == 0) {
    if (in != STDIN_FILENO) {
      dup2(in, STDIN_FILENO); 
      close(in);
    }
    if (out != STDOUT_FILENO) {
      dup2(out, STDOUT_FILENO);
      close(out);
    }

    char *path = tokens_get_token(tokens, 0);
    char resolved_path[1024];
    int error = resolve_path(path, resolved_path);
    if (error == -1) {
      strcpy(resolved_path, path); 
    }
    redirect(tokens);
    int num_para = tokens_get_length(tokens);
    char **argv = malloc(sizeof(char*) * (1+num_para));
    int cnt = 0;
    for (int i = 0; i < num_para; i++) {
      char *token = tokens_get_token(tokens, i);
      if (token[0] == '<' || token[0] == '>') {
        i++;
        continue;
      }
      argv[cnt++] = token;
    }
    argv[cnt] = NULL;

    execv(resolved_path, argv);
    printf("%s is not found or not able to execute\n", path);
    free(argv);
    exit(-1);
  } else {
    wait (NULL);
  }
}

int main(unused int argc, unused char *argv[]) {
  init_shell();

  static char line[4096];
  int line_num = 0;
 
  /* Please only print shell prompts when standard input is not a tty */
  if (shell_is_interactive)
    fprintf(stdout, "[%d] %d: ", getpid(), line_num);

  while (fgets(line, 4096, stdin)) {
    struct tokens *programs = tokenize(line, '|');
    int len = tokens_get_length(programs);

    int in = STDIN_FILENO, out = STDOUT_FILENO;
    for (int i = 0; i < len; i++) {

      /* Split our line into words. */
      struct tokens *tokens = tokenize(tokens_get_token(programs, i), ' ');

      /* Find which built-in function to run. */
      int fundex = lookup(tokens_get_token(tokens, 0));

      if (fundex >= 0) {
        cmd_table[fundex].fun(tokens);
      } else {
        if (i != len - 1 && pipe(pipefd) == -1) {
          perror("pipe");
          exit(-1);
        }
        if (i != len - 1) out = pipefd[1];
        execute_user_program(tokens, in, out);

        if (i != len - 1) {
          close(pipefd[1]);
          in = pipefd[0];
        }
      }

      if (i == len - 1 && shell_is_interactive)
        /* Please only print shell prompts when standard input is not a tty */
        fprintf(stdout, "[%d] %d: ", getpid(), ++line_num);

      /* Clean up memory */
      tokens_destroy(tokens);
    }

    tokens_destroy(programs);
  }

  return 0;
}
