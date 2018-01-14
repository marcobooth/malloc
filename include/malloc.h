/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:26:28 by mbooth            #+#    #+#             */
/*   Updated: 2017/12/03 15:27:51 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include "libft.h"
# include <pthread.h>

# define TRUE 1
# define FALSE 0

# define TINY 300
# define SMALL 3000

/*
**	Thanks to flenge for the idea
*/

typedef struct	s_map_info {
	t_list		list;
	size_t		allocations;
}				t_map_info;

typedef struct	s_alloc_info {
	t_list		list;
	size_t		size;
	t_map_info	*map_of_this_allocation;
}				t_alloc_info;

typedef struct	s_env_info {
	t_list		*maps;
	t_list		*allocations;
	void		*next_location;
	void		*end_location;
	t_map_info	*current_map;
	size_t		env_size;
}				t_env_info;

typedef struct	s_malloc_info {
	t_env_info	tiny;
	t_env_info	small;
	t_list		*large_maps;
}				t_malloc_info;

extern t_malloc_info	*g_malloc_info;
extern pthread_mutex_t	g_mutex_count;

void			*malloc(size_t size);
void			show_alloc_mem();
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			print_pointer(void *ptr);
void			print_list(t_list *list);
void			list_push_back(t_list **begin_list,
								void *data, t_list *new_one);
void			*get_mmap(size_t size);
void			*reallocf(void *ptr, size_t size);
void			*reallocate_pointer(t_list **original,
						t_list *to_reallocate, size_t size);
void			*locked_malloc(size_t size);
void			locked_free(void *ptr);

#endif
