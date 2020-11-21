#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define HIGH 20
#define FREQ 80
#define SAMPLES 20

typedef struct pte{
  int present;
  int id;
  struct pte *next;
  struct pte *prev;
} pte;

void init(int *sequence, int refs, int pages){
  int high = (int)(pages * ((float)HIGH/100));
  
  for(int i = 0; i < refs; i++){
    if(rand()%100 < FREQ){
      /* the freq case */
      sequence[i] = rand()%high;
    }
    else{
      /* the less freq case */
      sequence[i] = high + rand()%(pages-high);
    }
  }
}

void clear_page_table(pte *page_table, int pages){
  for(int i = 0; i < pages; i++){
    page_table[i].present = 0;
  }
}


int simulate(int *seq, pte *table, int refs, int frms, int pgs){
  int hits = 0;
  int allocated = 0;

  pte *first = NULL;
  pte *last = NULL;
  
  int i;

  for(i = 0; i < refs; i++){
    int next = seq[i];
    pte *entry = &table[next];

    if(entry->present == 1){
      hits++;

      if(entry->prev == NULL){
	first = entry->next;
	first->prev = NULL;
	last->next = entry;
	entry->prev = last;
	last = entry;
	last->next = NULL;
      }
      else if(entry->next == NULL){}
      else {
	pte *before = entry->prev;
	pte *after = entry->next;
	after->prev = before;
	before->next = after;
	last->next = entry;
	entry->prev = last;
	last = entry;
	last->next = NULL;
      }

      
    } else {
      if(allocated < frms){
	allocated++;

	entry->present = 1;
	entry->prev = last;
	entry->next = NULL;

	if(first == NULL){
	  first = entry;
	  last = entry;
	}
	else {
	  last->next = entry;
	  entry->prev = last;
	  last = entry;
	}

	  
      } else {
	pte *evict;
	
	evict = first;

	first = evict->next;
	first->prev = NULL;

	evict->present = 0;

	entry->present = 1;
	entry->prev = last;
	entry->next = NULL;

	last->next = entry;
	last = entry;
	
      }
    }
  }
  return hits; 
}


int main(int argc, char *argv[]){
  /* could be command line arguments */
  int refs = atoi(argv[1]);
  int pages = atoi(argv[2]);

  pte *table = (pte *) malloc(pages * sizeof(pte));
  
  int *sequence = (int*)malloc(refs * sizeof(int));

  init(sequence, refs, pages);

  printf("# This is a benchmark of random replacement\n");
  printf("# %d page references\n",refs);
  printf("# %d pages \n", pages);
  printf("#\n#\n#frames\tratio\n");

  /* frames is the size of the memory in frames */
  int frames;

  int incr = pages/SAMPLES;

  for(frames = incr; frames <= pages; frames += incr){

    /* clear page tables entries */
    clear_page_table(table,pages);

    int hits = simulate(sequence, table, refs, frames, pages);

    float ratio = (float)hits/refs;
    

    printf("%d\t%.2f\t\n", frames, ratio);
  }

  return 0;
}
