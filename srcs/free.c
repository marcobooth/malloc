#include "malloc.h"

void print_list(t_list *list) {
  int i;

  i = 0;
  while (list) {
    ft_putstr("List number is ");
    ft_putnbr(i);
    ft_putstr("\n");
    print_pointer(list);
		ft_putstr("\n");
    list = list->next;
    i += 1;
  }
}

void list_remove(t_list **original, t_list *to_remove) {
	if (original && *original && to_remove)
	{
		if (*original == to_remove)
			*original = (*original)->next;
		else
			return list_remove(&((*original)->next), to_remove);
	}
}

int					list_remove_node(t_list **original, t_list *to_remove, t_env_info *env)
{
	t_alloc_info	*alloc_info;

	if (original && *original && to_remove)
	{
		if (*original == to_remove)
		{
			*original = (*original)->next;
			alloc_info = (t_alloc_info*)to_remove;
			alloc_info->map_of_this_allocation->allocations -= 1;
			if (alloc_info->map_of_this_allocation->allocations == 0) {
				//Either reuse the current mmap. Should it be bzerod?
				if (alloc_info->map_of_this_allocation == (t_map_info*)env->current_map) {
					env->next_available_location = (void*)env->current_map + sizeof(t_map_info);
					// ft_putstr("Current mmap");
					// print_pointer(env->current_map);
					// ft_putstr("\n");
					// ft_putstr("Next available location: ");
					// print_pointer(env->next_available_location);
					// ft_putstr("\n");
				}
				// Or remove it from the list (because another available one already exists)
				else {
					// ft_putstr("MUNMAPPING");
					munmap(alloc_info->map_of_this_allocation, env->env_size);
					list_remove(&env->maps, (void*)alloc_info->map_of_this_allocation);
				}
			}
      return(TRUE);
		}
		else
			return list_remove_node(&((*original)->next), to_remove, env);
	}

  return(FALSE);
}

int deallocate_pointer(t_env_info *env, void *ptr) {
  int i;
	// ft_putstr("Initial list: \n");
  // print_list(env->allocations);
  i = list_remove_node(&env->allocations, ptr, env);
  // ft_putstr("Removed or not: ");
  // ft_putnbr(i);
  // ft_putstr("\n");
	// ft_putstr("List after change: \n");
  // print_list(env->allocations);
  return(i);
  // remove map if 0 allocations, bzero? should be done in this function
}

void       free(void *ptr) {
  int pointer_freed;

	if (g_malloc_info == NULL || ptr == NULL) {
		return;
	}

  ptr = ptr - sizeof(t_alloc_info);
  pointer_freed = deallocate_pointer(&g_malloc_info->tiny, ptr);
  if (pointer_freed == FALSE) {
    pointer_freed = deallocate_pointer(&g_malloc_info->small, ptr);
  }
  // if (pointer_freed == FALSE) {
  //   pointer_freed = list_remove_node(&g_malloc_info->large_maps, ptr);
  // }
}
