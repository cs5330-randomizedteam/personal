/*
 * mm_alloc.c
 */

#include "mm_alloc.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>


static struct mm_block *block_head = NULL;
static rlim_t data_limit = 0;

void* _mm_malloc(size_t size, void *ptr, size_t copy_size)
{ 
  if (size == 0) return NULL;
  struct mm_block *block_cur = block_head, *block_prev = NULL;
  while (block_cur != NULL) {
  	if (block_cur->is_free && block_cur->size >= size) {
      block_cur->is_free = 0;
      if (block_cur->size > size + sizeof(struct mm_block)) {  
        size_t remain_size = block_cur->size - size - sizeof(struct mm_block);
        block_cur->size = size;

        if (ptr != NULL) memmove(block_cur + 1, ptr, copy_size); // for realloc=

        struct mm_block *next_block = (void*)block_cur + size + sizeof(struct mm_block);
        next_block->size = remain_size;
        next_block->is_free = 1;
        next_block->prev = block_cur;
        next_block->next = block_cur->next;
        if (next_block->next != NULL) next_block->next->prev = next_block;
        block_cur->next = next_block;
      }

      void* mm = (void*)block_cur + sizeof(struct mm_block);
      if (ptr == NULL) memset(mm, 0, size);
      return mm;

  	} else {
  	  block_prev = block_cur;
  	  block_cur = block_cur->next;
  	}
  }

  if (data_limit == 0) {
  	struct rlimit temp;
  	if (getrlimit(RLIMIT_DATA, &temp) == -1) return NULL;
  	data_limit = temp.rlim_max;
  }

  size_t alloc_size = size + sizeof(struct mm_block);
  if ((rlim_t)(sbrk(0) + alloc_size) >= data_limit) return NULL;

  struct mm_block *new_block = sbrk(alloc_size);
  new_block->size = size;
  new_block->is_free = 0;
  new_block->next = NULL;
  new_block->prev = block_prev;

  if (block_prev != NULL) block_prev->next = new_block;
  else block_head = new_block;
  
  void* mm = (void*)new_block + sizeof(struct mm_block);
  if (ptr == NULL) memset(mm, 0, size);
  else memmove(mm, ptr, copy_size);
  return mm;
}

size_t _mm_free(void* ptr) {
  if (ptr == NULL) return 0;
  struct mm_block *block_cur = block_head;
  while (block_cur != NULL) {
    if (block_cur + 1 == ptr && !block_cur->is_free) {
      int free_size = block_cur->size;
      block_cur->is_free = 1;
      if (block_cur->prev != NULL && block_cur->prev->is_free) {
        block_cur->prev->size += sizeof(struct mm_block) + block_cur->size;
        block_cur->prev->next = block_cur->next;
        if (block_cur->next != NULL) block_cur->next->prev = block_cur->prev;
        block_cur = block_cur->prev;
      }
      if (block_cur->next != NULL && block_cur->next->is_free) {
        block_cur->size += sizeof(struct mm_block) + block_cur->next->size;
        if (block_cur->next->next != NULL) block_cur->next->next->prev = block_cur;
        block_cur->next = block_cur->next->next;
      }
      return free_size;
    }
    block_cur = block_cur->next;
  }
  return 0;
}


void* mm_malloc(size_t size) {
  return _mm_malloc(size, NULL, 0);
}


void* mm_realloc(void* ptr, size_t size)
{
  if (ptr == NULL) return mm_malloc(size);
  if (size == 0) {
    mm_free(ptr);
    return NULL;
  }

  size_t original_size = _mm_free(ptr);
  if (original_size == 0) return NULL;
  return _mm_malloc(size, ptr, original_size);
}

void mm_free(void* ptr)
{ 
  _mm_free(ptr);
}
