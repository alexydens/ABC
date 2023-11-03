/*
 * This contains the struct and functions for a linear allocator of heap memory
 * in C. This is also known as an arena, hence the header's and structure's
 * name.
 */

#if !defined (ARENA_ALLOC_H)
#define ARENA_ALLOC_H

/* Core */
#include "base.h"

/* The type for an arena */
typedef struct {
  u8* start;
  u8* end;
  u8* current;
} Arena;

/* Create a linear allocator */
Arena createArena(size_t size);

/* Allocate some memory with the linear allocator */
void* arena_alloc(Arena* arena, size_t size);

/* Free the linear allocator (This frees it IN FULL, the data is GONE) */
void arena_free(Arena* arena);

#endif /* ARENA_ALLOC_H */
