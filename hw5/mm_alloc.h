/*
 * mm_alloc.h
 *
 * Exports a clone of the interface documented in "man 3 malloc".
 */

#pragma once

#ifndef _malloc_H_
#define _malloc_H_

#include <stdlib.h>

struct mm_block {
	size_t size;
	int is_free;
	struct mm_block *next;
	struct mm_block *prev;
};


void* mm_malloc(size_t size);
void* mm_realloc(void* ptr, size_t size);
void mm_free(void* ptr);

//TODO: Add any implementation details you might need to this file

#endif
