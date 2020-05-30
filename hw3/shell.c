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
  char* dir = getcwd(NULL, 0);
  if (dir != NULL) {
    printf("%s\n", dir);
    free(dir);
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

char* resolve_path(const char* path) {
  int n = tokens_get_length(PATH);
  char *temp = malloc(sizeof(char) * 1024);
  for (int i = 0; i < n; i++) {
    char* dir = tokens_get_token(PATH, i);
    int len = strlen(dir);
    strcpy(temp, dir);
    temp[len] = '/', temp [len+1] = '\0';
    strcat(temp, path);
    if (access(temp, F_OK) != -1) {
      char* resolved_path = malloc(sizeof(char) * strlen(temp));
      strcpy(resolved_path, temp);
      free(temp);
      return resolved_path;
    }
  }
  free(temp);
  return NULL;
}

void execute_user_program(struct tokens *tokens) {
  int pid = fork();
    if (pid == 0) {
      char *path = tokens_get_token(tokens, 0);
      char *resolved_path = resolve_path(path);
      if (resolved_path == NULL) {
        printf("%s is not found\n", path);
        exit(-1);
      }
      int num_para = tokens_get_length(tokens);
      char **argv = malloc(sizeof(char*) * (1+num_para));
      for (int i = 0; i < num_para; i++) {
        argv[i] = tokens_get_token(tokens, i);
      }
      argv[num_para] = NULL;
      execv(resolved_path, argv);
      printf("%s is failed to execute\n", path);
      free(argv);
      free(resolved_path);
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
    /* Split our line into words. */
    struct tokens *tokens = tokenize(line, ' ');

    /* Find which built-in function to run. */
    int fundex = lookup(tokens_get_token(tokens, 0));

    if (fundex >= 0) {
      cmd_table[fundex].fun(tokens);
    } else {
      execute_user_program(tokens);
    }

    if (shell_is_interactive)
      /* Please only print shell prompts when standard input is not a tty */
      fprintf(stdout, "[%d] %d: ", getpid(), ++line_num);

    /* Clean up memory */
    tokens_destroy(tokens);
  }

  return 0;
}
