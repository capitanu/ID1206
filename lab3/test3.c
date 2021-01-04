#include <stdio.h>
#include "green.h"

int flag = 0;
green_cond_t cond;

void *test(void *arg){
  int id = *(int*)arg;
  int loop = 4;
  while(loop > 0){
    printf("thread %d: %d\n", id, loop);
    loop--;
    flag = (id + 1) % 2;
    if(id == 1){
      for(int i = 0; i < 8239000; i++);
    }
    else {
      for(int i = 0; i < 823900; i++);
    }
  }
  printf("finished thread: %d\n", id);
}


int main(){

  green_t g0, g1;
  int a0 = 0;
  int a1 = 1;
  g0.name = "g0";
  g1.name = "g1";

  cond = green_cond_init();
  
  green_create(&g0, test, &a0);
  green_create(&g1, test, &a1);

  green_join(&g0, NULL);
  
  green_join(&g1, NULL);

  printf("done\n");

  return 0;
}

