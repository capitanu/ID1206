#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(){
  int pid = fork();
  if(pid == 0){
    int child = getpid();
    printf("child: parent %d, group %d\n", getppid(), getpgid(child));
    }
  else{
    int parent = getpid();
    printf("I'm the mother process %d in group %d\n", parent, getpgid(parent));
    wait(NULL);
  }
}
