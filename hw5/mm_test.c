#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

/* Function pointers to hw3 functions */
void* (*mm_malloc)(size_t);
void* (*mm_realloc)(void*, size_t);
void (*mm_free)(void*);

void load_alloc_functions() {
    void *handle = dlopen("hw3lib.so", RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    char* error;
    mm_malloc = dlsym(handle, "mm_malloc");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    mm_realloc = dlsym(handle, "mm_realloc");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    mm_free = dlsym(handle, "mm_free");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
}

int main() {
    load_alloc_functions();

    int *data = (int*) mm_malloc(sizeof(int));
    assert(data != NULL);
    data[0] = 354;
    printf("data is %d\n", data[0]);

    char *bytedata = (char*) mm_malloc(sizeof(char));
    assert(bytedata != NULL);
    bytedata[0] = 'x';
    printf("data is %c\n", bytedata[0]);


    char *bytedata1 = (char*) mm_malloc(sizeof(char));
    assert(bytedata1 != NULL);
    bytedata1[0] = 'y';
    printf("data is %c\n", bytedata1[0]);

    char *bytedata2 = (char*) mm_malloc(sizeof(char));
    assert(bytedata2 != NULL);
    bytedata2[0] = 'z';
    printf("data is %c\n", bytedata2[0]);

    char *bytedata3 = (char*) mm_malloc(sizeof(char));
    assert(bytedata3 != NULL);
    bytedata3[0] = 'z';
    printf("data is %c\n", bytedata3[0]);

    char *bytedata4 = (char*) mm_malloc(sizeof(char));
    assert(bytedata4 != NULL);
    bytedata4[0] = 'z';
    printf("data is %c\n", bytedata4[0]);

    // mm_free(bytedata);
    // mm_free(bytedata1);
    // mm_free(bytedata3);

    printf("last address: %p\n", bytedata4);
    char* reloc_data = mm_realloc(bytedata2, sizeof(int));
    printf("next: %p\n", reloc_data);
    printf("actual: %c\n", *reloc_data);


    mm_free(data);
    printf("malloc test successful!\n");

    return 0;
}
