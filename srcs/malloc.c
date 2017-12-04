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

t_malloc_info *g_malloc_info = NULL;

void *get_mmap(size_t size) {
  // mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
  // PROT_READ   Pages may be read
  // PROT_WRITE  Pages may be written
  // MAP_ANON          Map anonymous memory not associated with any specific file
  // MAP_PRIVATE       Modifications are private (copy-on-write)
  return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

t_malloc_info *set_up_environment() {
  if (g_malloc_info == NULL) {
    g_malloc_info = get_mmap(sizeof(t_malloc_info));
    ft_bzero(g_malloc_info, sizeof(t_malloc_info));
    g_malloc_info->tiny.env_size = (100 * (TINY + sizeof(t_alloc_info))) + sizeof(t_map_info); // + room for the info
    g_malloc_info->small.env_size = (100 * (SMALL + sizeof(t_alloc_info))) + sizeof(t_map_info); // + room for the info
  }

  return (g_malloc_info);
}

void *tiny_or_small(size_t size, t_env_info *env_info) {
  void *new_map;

  if ( !env_info->next_available_location
    || !(env_info->next_available_location + size < env_info->end_location)
    ) {
      new_map = get_mmap(env_info->env_size);
      env_info->next_available_location = new_map;
      env_info->end_location = new_map + env_info->env_size;
      ft_putstr("1");
      // printf("\nNumber: %zu\n", env_info->env_size);
      // printf("%p\n", env_info->next_available_location);
      // printf("%p\n", env_info->end_location);
  } else {
    new_map = NULL;
    env_info->next_available_location = env_info->end_location + env_info->env_size;
    ft_putstr("0");
  }
  (void)size;
  return new_map;
}

void *malloc(size_t size) {
  t_malloc_info *env;
  void          *memory;

  env = set_up_environment();
  // if (size < TINY) {
    // memory =
  tiny_or_small(size, &env->tiny);
  // }
  // else if (size < SMALL) {
  //   memory = tiny_or_small(size, env->small);
  // } else {
    memory = get_mmap(size);
  // }

  return (memory);
}
