/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:33:35 by mbooth            #+#    #+#             */
/*   Updated: 2018/01/12 19:33:40 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	list_remove(t_list **original, t_list *to_remove)
{
	if (original && *original && to_remove)
	{
		if (*original == to_remove)
			*original = (*original)->next;
		else
			return (list_remove(&((*original)->next), to_remove));
	}
}

void	deallocate_tiny_or_small(t_env_info *env, t_alloc_info *alloc_info)
{
	alloc_info->map_of_this_allocation->allocations -= 1;
	if (alloc_info->map_of_this_allocation->allocations == 0)
	{
		if (alloc_info->map_of_this_allocation == (t_map_info*)env->current_map)
		{
			env->next_location = (void*)env->current_map
													+ sizeof(t_map_info);
		}
		else
		{
			list_remove(&env->maps, (void*)alloc_info->map_of_this_allocation);
			munmap(alloc_info->map_of_this_allocation, env->env_size);
		}
	}
}

/*
** if env == NULL is for large maps
*/

int		deallocate_pointer(t_list **original,
						t_list *to_remove, t_env_info *env)
{
	t_alloc_info	*alloc_info;

	ft_putstr("\nchecking original and to remove:");
	print_pointer(*original);
	ft_putstr(" ");
	print_pointer(to_remove);
	ft_putstr("\n");
	if (!original || !(*original) || !to_remove)
		return (FALSE);
	if (*original == to_remove)
	{
		*original = (*original)->next;
		alloc_info = (t_alloc_info*)to_remove;
		if (env == NULL)
			munmap(to_remove, alloc_info->size);
		else {
			ft_putstr("\nthis is getting called\n");
			deallocate_tiny_or_small(env, alloc_info);
		}
		return (TRUE);
	}
	else
		return (deallocate_pointer(&((*original)->next), to_remove, env));
	return (FALSE);
}

void	locked_free(void *ptr)
{
	ft_putstr("\nlocked_free:");
	print_pointer(ptr);
	ft_putstr("\n");
	int pointer_freed;

	if (g_malloc_info == NULL || ptr == NULL)
	{
		return ;
	}
	ptr = ptr - sizeof(t_alloc_info);
	ft_putstr("\nabout to print the list\n");
	print_list(g_malloc_info->tiny.allocations);
	pointer_freed = deallocate_pointer(&g_malloc_info->tiny.allocations,
								ptr, &g_malloc_info->tiny);
	if (pointer_freed == FALSE)
		pointer_freed = deallocate_pointer(&g_malloc_info->small.allocations,
								ptr, &g_malloc_info->small);
	if (pointer_freed == FALSE)
		pointer_freed = deallocate_pointer(&g_malloc_info->large_maps,
										ptr, NULL);
	ft_putstr("\ndid the pointer free? ");
	ft_putnbr(pointer_freed);
	ft_putstr("\n");
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex_count);
	locked_free(ptr);
	pthread_mutex_unlock(&g_mutex_count);
}
