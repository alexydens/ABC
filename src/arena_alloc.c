#include "arena_alloc.h"

/* Create a linear allocator */
Arena createArena(size_t size) {
  Arena arena;
  arena.start = malloc(size);
  arena.end = arena.start + size;
  arena.current = arena.start;
  return arena;
}

/* Allocate some memory with the linear allocator */
void* arena_alloc(Arena* arena, size_t size) {
  void* ret = (void*) arena->current;
  if (!(arena->current + size <= arena->end)) *(i32*)0 = 0;
  arena->current += size;
  return ret;
}

/* Free the linear allocator (This frees it IN FULL, the data is GONE) */
void arena_free(Arena* arena) {
  free(arena->start);
}
