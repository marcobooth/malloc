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

#include <stdio.h>
#include <sys/mman.h>
#include "libft.h"

# define TRUE 1
# define FALSE 0

# define TINY 100
# define MEDIUM 1000

# define ALLOCATIONS_PER_SIZE 100

typedef struct s_env_info {
  size_t env_size;
  char   *nothing;
} t_env_info;

typedef struct s_malloc_info {
  t_env_info tiny;
  t_env_info medium;
  // large
} t_malloc_info;

extern t_malloc_info *g_malloc_info;

void				*malloc(size_t size);

#endif
