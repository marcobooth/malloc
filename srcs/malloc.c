/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:09:41 by mbooth            #+#    #+#             */
/*   Updated: 2017/12/03 15:25:39 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	For understanding threads, this was pretty helpful:
**	https://www.ibm.com/developerworks/library/l-pthred/index.html#sidebar2
**	does it stop them going into another malloc or another anything
*/

t_malloc_info	*g_malloc_info = NULL;

/*
**	if this is called from another file, could it be NULL?
*/

pthread_mutex_t	g_mutex_count = PTHREAD_MUTEX_INITIALIZER;

/*
**  multiple of getpagesize()
*/

t_malloc_info	*set_up_environment(void)
{
	if (g_malloc_info == NULL)
	{
		g_malloc_info = get_mmap(sizeof(t_malloc_info));
		ft_bzero(g_malloc_info, sizeof(t_malloc_info));
		g_malloc_info->tiny.env_size = (100 *
										(TINY + sizeof(t_alloc_info)))
										+ sizeof(t_map_info);
		g_malloc_info->small.env_size = (100 *
										(SMALL + sizeof(t_alloc_info)))
										+ sizeof(t_map_info);
	}
	return (g_malloc_info);
}

/*
**  TEO: how exactly does alloc_info->list get initialised
**	(and to the same address as the memory)
*/

void			*large(size_t size, t_list **large_maps)
{
	void			*map;
	t_alloc_info	*alloc_info;

	map = get_mmap(size + sizeof(t_alloc_info));
	alloc_info = (t_alloc_info*)map;
	alloc_info->size = size;
	list_push_back(large_maps, NULL, &alloc_info->list);
	return (map + sizeof(t_alloc_info));
}

/*
**	line60 env_info->current_map->list = map;
**	why doesn't this need to be set??
*/

void			*tiny_or_small(size_t size, t_env_info *env_info)
{
	void			*map;
	void			*new_memory;
	t_alloc_info	*alloc_info;

	if (!env_info->next_location || !(env_info->next_location +
		sizeof(t_map_info) + size < env_info->end_location))
	{
		map = get_mmap(env_info->env_size);
		env_info->next_location = map + sizeof(t_map_info);
		env_info->end_location = map + env_info->env_size;
		env_info->current_map = (t_map_info*)map;
		list_push_back((t_list**)&env_info->maps, NULL,
						&env_info->current_map->list);
		env_info->current_map->allocations = 0;
	}
	alloc_info = (t_alloc_info*)env_info->next_location;
	alloc_info->size = size;
	alloc_info->map_of_this_allocation = env_info->current_map;
	new_memory = env_info->next_location + sizeof(t_alloc_info);
	env_info->next_location = env_info->next_location
										+ sizeof(t_alloc_info) + size;
	list_push_back(&env_info->allocations, &alloc_info->list,
						&alloc_info->list);
	env_info->current_map->allocations += 1;
	return (new_memory);
}

void			*locked_malloc(size_t size)
{
	t_malloc_info	*env;
	void			*memory;

	env = set_up_environment();
	if (!env)
		return (NULL);
	if (size < TINY)
		memory = tiny_or_small(size, &env->tiny);
	else if (size < SMALL)
		memory = tiny_or_small(size, &env->small);
	else
		memory = large(size, &env->large_maps);
	return (memory);
}

void			*malloc(size_t size)
{
	void	*address;

	pthread_mutex_lock(&g_mutex_count);
	address = locked_malloc(size);
	pthread_mutex_unlock(&g_mutex_count);
	return (address);
}
