#include <instance_allocator.h>

bool
instance_allocator_create(
    void* instance_data,
    fptr_inst_clean data_clean_func,
    fptr_inst_malloc malloc_func,
    fptr_inst_realloc realloc_func,
    fptr_inst_free free_func,
    instance_allocator_t* out_allocator
)
{
    if (instance_data == NULL)
        return false;

    *out_allocator = (instance_allocator_t) {
        .instance = {
            .data = instance_data,
            .clean_func = data_clean_func,
        },

        .malloc_func =  malloc_func,
        .realloc_func = realloc_func,
        .free_func =    free_func,
    };

    return true;
}

int instance_allocator_clean(instance_allocator_t* allocator)
{
    if (allocator == NULL || allocator->instance.data == NULL)
        return 0;

    allocator->malloc_func = NULL;
    allocator->realloc_func = NULL;
    allocator->free_func = NULL;

    if (allocator->instance.clean_func == NULL)
    {
        allocator->instance.data = NULL;
        return 1;
    }

    allocator->instance.clean_func(allocator->instance.data);
    return 2;
}

void* instance_allocator_malloc(instance_allocator_t* allocator, size_t size)
{
    if (allocator == NULL || allocator->malloc_func == NULL)
        return NULL;

    return allocator->malloc_func(allocator->instance.data, size);
}

void* instance_allocator_realloc(instance_allocator_t* allocator, void* ptr, size_t size)
{
    if (allocator == NULL || allocator->realloc_func == NULL)
        return NULL;

    return allocator->realloc_func(allocator->instance.data, ptr, size);
}

void instance_allocator_free(instance_allocator_t* allocator, void* ptr)
{
    if (allocator == NULL || allocator->free_func == NULL)
        return;

    allocator->free_func(allocator->instance.data, ptr);
}
