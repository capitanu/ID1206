#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){

  char *heap = malloc(20);
  *heap = 0x61;

  printf("heap pointing to: %p\n", *heap);

  free(heap);

  char *foo = malloc(20);
  *foo = 0x62;

  printf("foo pointing to: %p\n", *foo);

  *heap = 0x63;
  printf("or is it pointing to: 0x%x\n", *foo);

  /* long *heap = (unsigned long*) calloc(100, sizeof(unsigned long)); */

  /*  printf("heap pointing to: %p\n", heap); */

  /*  printf("\n\n"); */
  /* printf("heap[2]: 0x%lx\n", heap[2]); */
  /* printf("heap[1]: 0x%lx\n", heap[1]); */
  /* printf("heap[0]: 0x%lx\n", heap[0]); */
  /* printf("heap[-1]: 0x%lx\n", heap[-1]); */
  /* printf("heap[-2]: 0x%lx\n", heap[-2]); */


  /* printf("\n\n"); */
  /* free(heap); */
  
  /* printf("heap[2]: 0x%lx\n", heap[2]); */
  /* printf("heap[1]: 0x%lx\n", heap[1]); */
  /* printf("heap[0]: 0x%lx\n", heap[0]); */
  /* printf("heap[-1]: 0x%lx\n", heap[-1]); */
  /* printf("heap[-2]: 0x%lx\n", heap[-2]); */

  printf("\n\n");


  int pid = getpid();

  char command[50];
  sprintf(command, "cat /proc/%d/maps", pid);
  system(command);
  
  return 0;
  
}
