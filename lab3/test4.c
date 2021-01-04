#include <stdio.h>
#include "green.h"

int flag = 0;
green_cond_t cond;
green_mutex_t mutex;

int counter = 0;

void *test(void *arg){
  int id = *(int*)arg;
  int loop = 1000;
  printf("Started thread: %d\n", id);
  while(loop > 0){
    green_mutex_lock(&mutex);
    while(flag != id){
      green_mutex_unlock(&mutex);
      green_cond_wait(&cond, &mutex);
    }
    flag = (id + 1) % 2;
    counter++;
    green_cond_signal(&cond);
    green_mutex_unlock(&mutex);
    loop--;
  }
  printf("Finished thread: %d\n", id);
}


int main(){

  green_t g0, g1;
  int a0 = 0;
  int a1 = 1;
  g0.name = "g0";
  g1.name = "g1";

  green_cond_init(&cond);
  green_mutex_init(&mutex);
  
  green_create(&g0, test, &a0);
  green_create(&g1, test, &a1);

  green_join(&g0, NULL);
  
  green_join(&g1, NULL);
  
  printf("Result: %d\n", counter);
  printf("done\n");

  return 0;
}

