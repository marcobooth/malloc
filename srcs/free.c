#include "malloc.h"

int					list_remove_node(t_list **original, t_list *to_remove)
{
	t_list				*old_one;
	int						i;

	if (original && *original && to_remove)
	{
		if (*original == to_remove)
		{
      // ft_putstr("-------------REMOVING NODE---------------\n");
			old_one = *original;
			*original = (*original)->next;
      // print_pointer(to_remove);
      // ft_putstr("size of pointer: ");
      ft_putnbr(((t_alloc_info*)to_remove)->size);
      ft_putstr("\n");
      i = munmap(to_remove, ((t_alloc_info*)to_remove)->size + sizeof(t_alloc_info));
			ft_putstr("Munmap: ");
			ft_putnbr(i);
			ft_putstr("\n");
      return(TRUE);
		}
		else
			return list_remove_node(&((*original)->next), to_remove);
	}
  return(FALSE);
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

int deallocate_pointer(t_env_info *env, void *ptr) {
  int i;
  // print_list(env->allocations);
  // ft_putstr("------ REMOVING POINTER FROM LIST ----------\n");
  i = list_remove_node(&env->allocations, ptr);
  // ft_putstr("DID WE REMOVE A NODE: ");
  // ft_putnbr(i);
  // ft_putstr("\n");
  // print_list(env->allocations);
  return(i);
  // remove map if 0 allocations, bzero? should be done in this function
}

void       free(void *ptr) {
  // check for NULL
  // check if global variable exists
  int pointer_freed;


  ptr = ptr - sizeof(t_alloc_info);
  pointer_freed = deallocate_pointer(&g_malloc_info->tiny, ptr);
  if (pointer_freed == 0) {
    pointer_freed = deallocate_pointer(&g_malloc_info->small, ptr);
  }
  if (pointer_freed == 0 ) {
    pointer_freed = list_remove_node(&g_malloc_info->large_maps, ptr);
  }
  // ft_putstr("freed pointer: ");
  // ft_putnbr(pointer_freed);
  // ft_putstr("\n");
  // ft_putstr("Pointer to free ");
  // print_pointer(ptr);
  // allocation = (t_alloc_info*)list_find(g_malloc_info->tiny.allocations, ptr - sizeof(t_alloc_info), &compare_pointers);
  // if (allocation == NULL) {
  //   allocation = (t_alloc_info*)list_find(g_malloc_info->small.allocations, ptr - sizeof(t_alloc_info), &compare_pointers);
  // } else {
  //   deallocate_pointer(&g_malloc_info->tiny, ptr);
  // }
  // if (allocation == NULL) {
  //   ft_putstr("THIS IS LARGE");
  // }
  //
  // ft_putstr("Pointer to deallocate: ");
  // print_pointer((void*)allocation);
  // ft_putstr("\n");

}
