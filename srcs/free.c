#include "malloc.h"

int   compare_pointers(void *p1, void *p2) {
  // ft_putstr("p1: ");
  // print_pointer(p1);
  // ft_putstr("p2: ");
  // print_pointer(p2);
  if (p1 == p2) {
    // cmp should return 0 if same
    return (0);
  }

  return (1);
}

t_list			*list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
  ft_putstr("ft find: ");
  print_pointer(begin_list);
	if (begin_list == NULL) {
    ft_putstr("returning NULL -----\n");
    return (NULL);
  }

  ft_putstr("ft find data: ");
  print_pointer(begin_list->data);
	if (cmp(begin_list->data, data_ref) == 0) {
    ft_putstr("returning now\n");
    // print_pointer(begin_list->data);
    // ft_putstr("\n");
    // print_pointer(data_ref);
    // ft_putstr("\n");
    return (begin_list);
  }
	return (list_find(begin_list->next, data_ref, cmp));
}

void					list_remove_node(t_list **original, t_list *to_remove)
{
	t_list				*old_one;

	if (original && *original && to_remove)
	{
		if (*original == to_remove)
		{
      ft_putstr("-------------REMOVING NODE---------------");
			old_one = *original;
			*original = (*original)->next;
		}
		else
			list_remove_node(&((*original)->next), to_remove);
	}
}

void print_list(t_list *list) {
  int i;

  i = 0;
  while (list) {
    ft_putstr("List number is ");
    ft_putnbr(i);
    ft_putstr("\n");
    print_pointer(list);
    list = list->next;
    i += 1;
  }
}

void deallocate_pointer(t_alloc_info *allocation, t_env_info *env, void *ptr) {
  print_list(env->allocations);
  ft_putstr("------ REMOVING POINTER FROM LIST ----------\n");
  list_remove_node(&env->allocations, ptr - sizeof(t_alloc_info));
  print_list(env->allocations);
  munmap(ptr - sizeof(t_alloc_info), allocation->size);
  // remove map if 0 allocations, bzero?
}

void       free(void *ptr) {
  // check for NULL
  // check if global variable exists
  t_alloc_info *allocation;

  // ft_putstr("Pointer to free: ");
  // print_pointer(ptr - sizeof(t_alloc_info));
  // ft_putstr("\n");

  allocation = (t_alloc_info*)list_find(g_malloc_info->tiny.allocations, ptr - sizeof(t_alloc_info), &compare_pointers);
  if (allocation == NULL) {
    allocation = (t_alloc_info*)list_find(g_malloc_info->small.allocations, ptr - sizeof(t_alloc_info), &compare_pointers);
  }
  if (allocation == NULL) {
    ft_putstr("THIS IS LARGE");
  }
  //
  // ft_putstr("Pointer to deallocate: ");
  // print_pointer((void*)allocation);
  // ft_putstr("\n");
  deallocate_pointer(allocation, &g_malloc_info->tiny, ptr);

}
