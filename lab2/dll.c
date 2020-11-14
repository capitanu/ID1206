#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define HEAD sizeof(struct head)

#define MIN(size) (((size) > (8)) ? (size):(8))
#define LIMIT(size) (MIN(0) + HEAD + size)
#define MAGIC(memory) ((struct head*)memory - 1)
#define HIDE(block) (void*)((struct head*)block + 1)

#define ALIGN 8
#define ARENA (64*1024)

struct head {
  uint16_t bsize;
  uint16_t bfree;
  uint16_t size;
  uint16_t free;
  struct head *prev;
  struct head *next;
};


struct head *after(struct head *block){
  return (struct head*)((char*)block + sizeof(struct head) + block->size);
}

struct head *before(struct head *block){
  return (struct head*)((char*)block - block->bsize);
}

int main(){
  
  return 0;
}
