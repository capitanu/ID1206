#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include "dlmall.h"

#define LOOPS 10
#define NR_BLOCKS 100

int main(){  
  
  void *test[1000];
  for(int j = 0; j < NR_BLOCKS; j++){
    test[j] = dalloc(16);
  }
  for(int i = 0; i < NR_BLOCKS; i++){
    test[i] = 'a';
  }
  print_space_used();
  return 0;
}
