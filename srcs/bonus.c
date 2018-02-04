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

	pthread_mutex_lock(&g_mutex_count);
	if (size == 0 || count == 0)
		return (NULL);
	pointer = locked_malloc(count * size);
	ft_bzero(pointer, size);
	pthread_mutex_unlock(&g_mutex_count);
	return (pointer);
}

/*
**	If pointer is a null pointer, the realloc function
**	behaves like the malloc function for the specified size
*/

void	*reallocf(void *pointer, size_t size)
{
	void *reallocated_pointer;

	pthread_mutex_lock(&g_mutex_count);
	reallocated_pointer = locked_realloc(pointer, size);
	if (reallocated_pointer == NULL)
		locked_free(pointer);
	pthread_mutex_unlock(&g_mutex_count);
	return (reallocated_pointer);
}
