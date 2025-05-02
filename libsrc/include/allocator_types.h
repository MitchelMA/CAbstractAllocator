#ifndef ALLOCATOR_TYPES_H__
#define ALLOCATOR_TYPES_H__

#include <stddef.h>

typedef void* (*fptr_malloc)  (size_t);
typedef void* (*fptr_realloc) (void*, size_t);
typedef void  (*fptr_free)    (void*);


typedef void* (*fptr_inst_malloc)  (void*, size_t);
typedef void* (*fptr_inst_realloc) (void*, void*, size_t);
typedef void  (*fptr_inst_free)    (void*, void*);
typedef void  (*fptr_inst_clean)   (void*);

struct allocator_data_instace
{
    void* data;
    fptr_inst_clean clean_func;
};

enum allocator_type
{
    TYPE_ALLOCATOR_STATIC,
    TYPE_ALLOCATOR_INSTANCE,
};

typedef struct static_allocator
{
    fptr_malloc   malloc_func;
    fptr_realloc realloc_func;
    fptr_free       free_func;
} static_allocator_t;

typedef struct instance_allocator
{
    struct allocator_data_instace instance;

    fptr_inst_malloc   malloc_func;
    fptr_inst_realloc realloc_func;
    fptr_inst_free       free_func;
} instance_allocator_t;

typedef struct allocator
{
    union {
        static_allocator_t   stat;
        instance_allocator_t inst;
    } using_allocator;
    enum allocator_type type;
} allocator_t;


#endif // !ALLOCATOR_TYPES_H__

