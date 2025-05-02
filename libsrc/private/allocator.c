#include <allocator.h>
#include <static_allocator.h>
#include <instance_allocator.h>

#include <string.h>


// Local declerations

bool allocator_create_(enum allocator_type type, void* in_allocator, allocator_t* out_allocator);

// End local declerations

bool allocator_create_as_static(static_allocator_t* in_allocator, allocator_t* out_allocator)
{
    return allocator_create_(TYPE_ALLOCATOR_STATIC, (void*)in_allocator, out_allocator);
}

bool allocator_create_as_instance(instance_allocator_t* in_allocator, allocator_t* out_allocator)
{
    return allocator_create_(TYPE_ALLOCATOR_INSTANCE, (void*)in_allocator, out_allocator);
}

int allocator_clean(allocator_t* allocator)
{
    if (allocator == NULL || allocator->type == TYPE_ALLOCATOR_NONE)
        return 0;

    int ret_code = 1;
    if (allocator->type == TYPE_ALLOCATOR_INSTANCE)
        ret_code = instance_allocator_clean(&allocator->using_allocator.inst);

    memset(&allocator->using_allocator, 0, sizeof(allocator->using_allocator));
    allocator->type = TYPE_ALLOCATOR_NONE;
    return ret_code;
}

void* allocator_malloc(allocator_t* allocator, size_t size)
{
    if (allocator == NULL || allocator->type == TYPE_ALLOCATOR_NONE)
        return NULL;

    switch (allocator->type)
    {
        case TYPE_ALLOCATOR_STATIC:
            return static_allocator_malloc(&allocator->using_allocator.stat, size);

        case TYPE_ALLOCATOR_INSTANCE:
            return instance_allocator_malloc(&allocator->using_allocator.inst, size);

        default:
            break;
    }

    return NULL;
}

void* allocator_realloc(allocator_t* allocator, void* ptr, size_t size)
{
    if (allocator == NULL || allocator->type == TYPE_ALLOCATOR_NONE)
        return NULL;

    switch (allocator->type)
    {
        case TYPE_ALLOCATOR_STATIC:
            return static_allocator_realloc(&allocator->using_allocator.stat, ptr, size);

        case TYPE_ALLOCATOR_INSTANCE:
            return instance_allocator_realloc(&allocator->using_allocator.inst, ptr, size);

        default:
            break;
    }

    return NULL;
}

void allocator_free(allocator_t* allocator, void* ptr)
{
    if (allocator == NULL || allocator->type == TYPE_ALLOCATOR_NONE)
        return;

    switch (allocator->type)
    {
        case TYPE_ALLOCATOR_STATIC:
            static_allocator_free(&allocator->using_allocator.stat, ptr);
            break;

        case TYPE_ALLOCATOR_INSTANCE:
            instance_allocator_free(&allocator->using_allocator.inst, ptr);
            break;

        default:
            break;
    }

    return;
}

// Local implementations 

bool allocator_create_(enum allocator_type type, void* in_allocator, allocator_t* out_allocator)
{
    if (in_allocator == NULL)
        return false;

    if (type == TYPE_ALLOCATOR_STATIC)
    {
        *out_allocator = (allocator_t) {
            .using_allocator.stat = *(static_allocator_t*)in_allocator,
            .type = type
        };
        return true;
    }
    
    if (type == TYPE_ALLOCATOR_INSTANCE)
    {
        *out_allocator = (allocator_t) {
            .using_allocator.inst = *(instance_allocator_t*)in_allocator,
            .type = type
        };
        return true;
    }

    return false;
}

// End local implementations
