/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 21:02:54 by mbooth            #+#    #+#             */
/*   Updated: 2018/01/12 21:02:57 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	If memory for the new object cannot be allocated,
**	the old object is not deallocated and its value is unchanged.
*/

void	*reallocate_pointer(t_list **original,
							t_list *to_reallocate,
							size_t size)
{
	t_alloc_info	*alloc_info;
	void			*new_pointer;

	if (original && *original && to_reallocate)
	{
		if (*original == to_reallocate)
		{
			*original = (*original)->next;
			new_pointer = malloc(size);
			alloc_info = (t_alloc_info*)to_reallocate;
			ft_memcpy(new_pointer,
						(void*)to_reallocate + sizeof(t_alloc_info),
						alloc_info->size <= size ? alloc_info->size : size);
			free(to_reallocate);
			return (new_pointer);
		}
		else
			return (reallocate_pointer(&((*original)->next),
					to_reallocate, size));
	}
	return (NULL);
}

/*
**	If ptr is a null pointer, the realloc function
**	behaves like the malloc function for the specified size
*/

void	*realloc(void *ptr, size_t size)
{
	void *reallocated_pointer;

	if (g_malloc_info == NULL)
		return (NULL);
	if (ptr == NULL)
		return (malloc(size));
	ptr = ptr - sizeof(t_alloc_info);
	reallocated_pointer = reallocate_pointer(&g_malloc_info->tiny.allocations,
							ptr, size);
	if (reallocated_pointer == NULL)
		reallocated_pointer =
				reallocate_pointer(&g_malloc_info->small.allocations,
							ptr, size);
	if (reallocated_pointer == NULL)
		reallocated_pointer = reallocate_pointer(&g_malloc_info->large_maps,
							ptr, size);
	return (reallocated_pointer);
}
