#ifndef ALLOCATOR_H__
#define ALLOCATOR_H__

#include "allocator_types.h"

bool allocator_create_as_static(static_allocator_t* in_allocator, allocator_t* out_allocator);
bool allocator_create_as_instance(instance_allocator_t* in_allocator, allocator_t* out_allocator);

int allocator_clean(allocator_t* allocator);

void* allocator_malloc(allocator_t* allocator, size_t size);
void* allocator_realloc(allocator_t* allocator, void* ptr, size_t size);
void  allocator_free(allocator_t* allocator, void* ptr);

#endif // !ALLOCATOR_H__
