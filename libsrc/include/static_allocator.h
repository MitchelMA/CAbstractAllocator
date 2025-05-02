#ifndef STATIC_ALLOCATOR_H__
#define STATIC_ALLOCATOR_H__

#include "allocator_types.h"

#include <stdlib.h>


void* static_allocator_malloc(static_allocator_t* allocator, size_t size);
void* static_allocator_realloc(static_allocator_t* allocator, void* ptr, size_t size);
void static_allocator_free(static_allocator_t* allocator, void* ptr);


#endif // !STATIC_ALLOCATOR_H__

