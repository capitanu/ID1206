#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>

void print_space_used();
void print_flist();
void *dalloc(size_t request);
void *dfree(void *memory);
