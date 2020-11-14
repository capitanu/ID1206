#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


void zot(unsigned long *stop){
  unsigned long r = 0x3;

  unsigned long *i;

  for(i = &r; i <= stop; i++){
    printf("%p    0x%lx\n",i, *i);
  }
}

  void foo(unsigned long *stop){
    unsigned long q = 0x2;

    zot(stop);
  }

int main(){
  int pid = getpid();
  
  unsigned long p = 0x1;

  foo(&p);


 back:
  
  printf("p (0x%lx): %p\n", p , &p);
  printf("  back: %p \n", &&back);
  
  printf("\n\n/proc/%d/maps\n\n",pid);

  char *heap = malloc(20);
  printf("the heap variable at: %p\n", &heap);
  printf("pointing to: %p\n", heap);


  printf("\n\n");
  char command[50];
  
  sprintf(command,"cat /proc/%d/maps",pid);
  system(command);
  
  return 0;
}
