/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 21:10:32 by mbooth            #+#    #+#             */
/*   Updated: 2018/01/12 21:10:37 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_maps(t_list *maps, size_t map_size, char *title)
{
	t_map_info *map_info;

	ft_putstr(title);
	map_info = (t_map_info*)maps;
	while (map_info)
	{
		print_pointer(map_info);
		ft_putstr(" - ");
		print_pointer(map_info + map_size);
		ft_putstr(" (");
		ft_putnbr(map_info->allocations);
		ft_putstr(" allocation)\n");
		map_info = (t_map_info*)map_info->list.next;
	}
}

/*
**	if type if t_alloc_info and you add 32, the compiler adds 32 t_alloc_infos
**	either add 1 (t_alloc_info)
**	or add to void pointer
*/

void	print_allocations(t_list *allocations, char *title)
{
	t_alloc_info *alloc_info;

	ft_putstr(title);
	alloc_info = (t_alloc_info*)allocations;
	while (alloc_info)
	{
		print_pointer((alloc_info + 1));
		ft_putstr(" - ");
		print_pointer((void*)alloc_info +
						sizeof(t_alloc_info) +
						alloc_info->size);
		ft_putstr(" : ");
		ft_putnbr(alloc_info->size);
		ft_putstr(" bytes\n");
		alloc_info = (t_alloc_info*)alloc_info->list.next;
	}
}

/*
**	should I be giving the address here,
**	make a difference using the direct value?
*/

void	show_alloc_mem(void)
{
	if (g_malloc_info == NULL)
		return ;
	ft_putstr("---------- SHOW ALLOCATED MEMORY ----------\n");
	if (g_malloc_info->tiny.maps != NULL)
		print_maps(g_malloc_info->tiny.maps,
					g_malloc_info->tiny.env_size, "TINY maps:\n");
	if (g_malloc_info->tiny.allocations != NULL)
		print_allocations(g_malloc_info->tiny.allocations,
							"TINY allocations\n");
	if (g_malloc_info->small.maps != NULL)
		print_maps(g_malloc_info->small.maps,
					g_malloc_info->small.env_size, "SMALL maps:\n");
	if (g_malloc_info->small.allocations != NULL)
		print_allocations(g_malloc_info->small.allocations,
							"SMALL allocations:\n");
	if (g_malloc_info->large_maps != NULL)
		print_allocations(g_malloc_info->large_maps,
							"LARGE allocations:\n");
}
