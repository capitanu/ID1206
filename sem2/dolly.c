#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(){

  int pid;
  int x = 123;
  pid = fork();

  if(pid == 0){
    printf("  child: x is %d\n", x);
    x = 42;
    sleep(1);
    printf("  child: x is %d\n", x);
    printf("x is located at: %p\n", &x);
  }
  else {
    printf("  mother: x is %d\n", x);
    x = 13;
    sleep(1);
    printf("  mother: x is %d\n", x);
    printf("x is located at: %p\n", &x)
    wait(NULL);
  }

  printf("\n");
  

  return 0;
}
