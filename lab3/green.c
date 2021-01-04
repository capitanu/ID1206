#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <assert.h>
#include "green.h"
#include <signal.h>
#include <sys/time.h>

#define PERIOD 100

static sigset_t block;
void timer_handler(int);

#define FALSE 0
#define TRUE 1

#define STACK_SIZE 4096

static ucontext_t main_cntx = {0};
static green_t main_green = {"main", &main_cntx, NULL, NULL, NULL, NULL, NULL, FALSE};

static green_t *running = &main_green;

static void init() __attribute__((constructor));

green_t *ready = NULL;


void print_queue(){
  green_t *n = ready;
  while(n != NULL){
    printf("%s, ", n->name);
    n = n->next;
  }
  printf("\n");
}
void init(){
  getcontext(&main_cntx);
  sigemptyset(&block);
  sigaddset(&block, SIGVTALRM);

  struct sigaction act = {0};
  struct timeval interval;
  struct itimerval period;

  act.sa_handler = timer_handler;
  assert(sigaction(SIGVTALRM, &act, NULL) == 0);

  interval.tv_sec = 0;
  interval.tv_usec = PERIOD;
  period.it_interval = interval;
  period.it_value = interval;
  setitimer(ITIMER_VIRTUAL, &period, NULL);
  
}

void enqueue(green_t *thread){
  if(ready == NULL){
    ready = thread;
  } else {
    green_t *n = ready;
    while(n->next != NULL)
      n = n->next;
    n->next = thread;
  }
}

green_t *find_next(green_t *thread){
  green_t *n = ready;
  green_t *temp;
  /* while(n != NULL && n->join == NULL){ */
  /*   temp = n; */
  /*   enqueue(temp); */
  /*   n = n->next; */
  /*   temp->next = NULL; */
  /* } */
  ready = n->next;
  n->next = NULL;
  return n;
}


void timer_handler(int sig){
  sigprocmask(SIG_BLOCK, &block, NULL);
  green_t *susp = running;
  enqueue(susp);

  running = find_next(ready);
  swapcontext(susp->context, running->context);
  
  sigprocmask(SIG_UNBLOCK, &block, NULL);
}



void green_thread(){
  green_t *this = running;

  void *result = (*this->fun)(this->arg);
  
  //enqueue(this->join);
  
  this->retval = result;

  this->zombie = TRUE;
  
  running = this->join;
  
  setcontext(running->context);
  
}


int green_create(green_t *new, void *(*fun)(void*), void *arg){

  ucontext_t *cntx = (ucontext_t *) malloc(sizeof(ucontext_t));
  getcontext(cntx);

  void *stack = malloc(STACK_SIZE);

  cntx->uc_stack.ss_sp = stack;
  cntx->uc_stack.ss_size = STACK_SIZE;
  makecontext(cntx, green_thread, 0);

  new->context = cntx;
  new->fun = fun;
  new->arg = arg;
  new->next = NULL;
  new->join = NULL;
  new->retval = NULL;
  new->zombie = FALSE;
  
  enqueue(new);

  return 0;
}


int green_yield(){
  green_t * susp = running;

  enqueue(susp);

  //print_queue();

  running = find_next(ready);
  swapcontext(susp->context, running->context);
  return 0;
  
}

int green_join(green_t *thread, void **res){
  if(!thread->zombie){
    green_t *susp = running;

    thread->join = susp;
    
    
    running = find_next(thread);
    swapcontext(susp->context, running->context);
  }

  res = thread->retval;

  free(thread->context);

  return 0;
}


int green_mutex_init(green_mutex_t *mutex){
  mutex->taken = FALSE;
  // initialize the fields
}

void mutex_enqueue(green_mutex_t *mutex, green_t *susp){
  green_t *temp;
  if(mutex->susp == NULL){
    mutex->susp = susp;
  } else {
    temp = mutex->susp;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = susp;
  }
  susp->next = NULL;
}

int green_mutex_lock(green_mutex_t *mutex){
  sigprocmask(SIG_BLOCK, &block, NULL);

  green_t *susp = running;
  if(mutex->taken){
    
    mutex_enqueue(mutex, susp);
    
    running = find_next(ready);
    swapcontext(susp->context, running->context);      
  } else {
    mutex->taken = TRUE;
  }
  sigprocmask(SIG_UNBLOCK, &block, NULL);
  return 0;
}


int green_mutex_unlock(green_mutex_t *mutex){
  sigprocmask(SIG_BLOCK, &block, NULL);

  if(mutex->susp != NULL){
    green_t *temp = mutex->susp;
    enqueue(temp);
    mutex->susp = temp->next;
    temp->next = NULL;
  } else {
    mutex->taken = FALSE;
  }
  
  sigprocmask(SIG_UNBLOCK, &block, NULL);
  return 0;
}

void green_cond_init(green_cond_t *cond){
  cond = (green_cond_t *) malloc(sizeof(green_cond_t));
  cond->list = NULL;
}

void green_cond_wait(green_cond_t *cond, green_mutex_t *mutex){
  
  sigprocmask(SIG_BLOCK, &block, NULL);
  

  if(mutex != NULL){
    green_mutex_unlock(mutex);
    
    green_t *temp = cond->list;
    if(temp != NULL){
      while(temp->next != NULL){
	temp = temp->next;
      }
      temp->next = running;
    } else {
      cond->list = running;
    }
  }
  
  green_t *t = running;
  running = find_next(ready);
  swapcontext(t->context, running->context);

  if(mutex != NULL){
    if(mutex->taken){
      green_t *t = running;
      running = find_next(ready);
      swapcontext(t->context, running->context);
  
    } else {
      mutex->taken = TRUE;
    }
  }
  sigprocmask(SIG_UNBLOCK, &block, NULL);
  
}

void green_cond_signal(green_cond_t *cond){
  green_t *temp = cond->list;
  if(temp != NULL){
    green_t *next = cond->list;
    cond->list = next->next;
    temp->next = NULL;
    enqueue(temp);
  }
}
