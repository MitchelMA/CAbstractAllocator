#include <static_allocator.h>

static static_allocator_t default_static_alloc = {
    .malloc_func =   malloc,
    .realloc_func = realloc,
    .free_func =       free,
};

void* static_allocator_malloc(static_allocator_t* allocator, size_t size)
{
    if (allocator == NULL || allocator->malloc_func == NULL)
        return default_static_alloc.malloc_func(size);

    return allocator->malloc_func(size);
}

void* static_allocator_realloc(static_allocator_t* allocator, void* ptr, size_t size)
{
    if (allocator == NULL || allocator->realloc_func == NULL)
        return default_static_alloc.realloc_func(ptr, size);

    return allocator->realloc_func(ptr, size);
}

void static_allocator_free(static_allocator_t* allocator, void* ptr)
{
    if (allocator == NULL || allocator->free_func == NULL)
    {
        default_static_alloc.free_func(ptr);
        return;
    }

    allocator->free_func(ptr);
}
