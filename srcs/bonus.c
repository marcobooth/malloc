#include "malloc.h"

//  Allocates a block of memory for an array of num elements,
//  each of them size bytes long, and initializes all its bits to zero
void *calloc(size_t count, size_t size) {
  void *pointer;

  if (size == 0 || count == 0)
    return (NULL);

  pointer = malloc(count * size);
  ft_bzero(pointer, size);

  return (pointer);
}

void       *reallocf(void *ptr, size_t size) {
	void *reallocated_pointer;

	if (g_malloc_info == NULL)
		return NULL;
	// If ptr is a null pointer, the realloc function behaves like the malloc function for the specified size
	if (ptr == NULL)
		return(malloc(size));

	ptr = ptr - sizeof(t_alloc_info);
	reallocated_pointer = reallocate_pointer(&g_malloc_info->tiny.allocations, ptr, size);
	if (reallocated_pointer == NULL)
		reallocated_pointer = reallocate_pointer(&g_malloc_info->small.allocations, ptr, size);
	if (reallocated_pointer == NULL)
		reallocated_pointer = reallocate_pointer(&g_malloc_info->large_maps, ptr, size);
  if (reallocated_pointer == NULL)
    free(ptr);

	return reallocated_pointer;
}
