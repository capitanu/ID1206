#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include "dlmall.h"

#define LOOPS 10
#define MAX_SIZE 100

int main(){
  int *try1 = dalloc(sizeof(int));
  *try1 = 1;
  printf("Data stored: %d\n\n", *try1);
  dfree(try1);
  int *test;
  for(int i = 0; i < LOOPS; i++){
    test = dalloc(rand()%MAX_SIZE);
    if(i%2 == 0){
      dfree(test);
    }
  
    printf("Iteration %d\n", i);
    print_flist();
  }
  
  return 0;
}
