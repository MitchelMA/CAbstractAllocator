#ifndef INSTANCE_ALLOCATOR_H__
#define INSTANCE_ALLOCATOR_H__

#include "allocator_types.h"

#include <stdbool.h>

bool
instance_allocator_create(
    void* instance_data,
    fptr_inst_clean data_clean_func,
    fptr_inst_malloc malloc_func,
    fptr_inst_realloc realloc_func,
    fptr_inst_free free_func,
    instance_allocator_t* out_allocator
);

int instance_allocator_clean(instance_allocator_t* allocator);

void* instance_allocator_malloc(instance_allocator_t* allocator, size_t size);
void* instance_allocator_realloc(instance_allocator_t* allocator, void* ptr, size_t size);
void instance_allocator_free(instance_allocator_t* allocator, void* ptr);


#endif // !INSTANCE_ALLOCATOR_H__

