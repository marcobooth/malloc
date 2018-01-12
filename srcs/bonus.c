/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:59:51 by mbooth            #+#    #+#             */
/*   Updated: 2018/01/12 19:01:08 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Allocates a block of memory for an array of num elements,
**	each of them size bytes long, and initializes all its bits to zero
*/

void	*calloc(size_t count, size_t size)
{
	void *pointer;

	if (size == 0 || count == 0)
		return (NULL);
	pointer = malloc(count * size);
	ft_bzero(pointer, size);
	return (pointer);
}

/*
**	If pointer is a null pointer, the realloc function
**	behaves like the malloc function for the specified size
*/

void	*reallocf(void *pointer, size_t size)
{
	void *realloc_ed;

	if (g_malloc_info == NULL)
		return (NULL);
	if (pointer == NULL)
		return (malloc(size));
	pointer = pointer - sizeof(t_alloc_info);
	realloc_ed = reallocate_pointer(&g_malloc_info->tiny.allocations,
													pointer, size);
	if (realloc_ed == NULL)
		realloc_ed = reallocate_pointer(&g_malloc_info->small.allocations,
													pointer, size);
	if (realloc_ed == NULL)
		realloc_ed = reallocate_pointer(&g_malloc_info->large_maps,
													pointer, size);
	if (realloc_ed == NULL)
		free(pointer);
	return (realloc_ed);
}
