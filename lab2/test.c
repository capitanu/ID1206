#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include "dlmall.h"

#define LOOPS 10000
#define NR_BLOCKS 10000
#define MAX_SIZE 40000

int main(){  
  
  void *test;
  for(int i = 0; i < LOOPS; i++){
    for(int j = 0; j < NR_BLOCKS; j++){
      test = dalloc(rand()%MAX_SIZE);
      if(j%3 == 0){
	void *test2 = dalloc(rand()%MAX_SIZE);
	void *test3 = dalloc(rand()%MAX_SIZE);
	void *test4 = dalloc(rand()%MAX_SIZE);
	dfree(test);
      }
    }
    //    printf("Iteration %d\n", i);
    print_flist();
  }
  print_space_used();
  
  return 0;
}
