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
    ft_putstr("im here");
    g_malloc_info = get_mmap(sizeof(t_malloc_info));
    g_malloc_info->tiny.env_size = (100 * TINY); // + room for the info
    g_malloc_info->medium.env_size = (100 * MEDIUM); // + room for the info
    g_malloc_info->tiny.nothing = "small nothing\n";
    g_malloc_info->medium.nothing = "medium nothing\n";
  }

  return (g_malloc_info);
}

void *malloc(size_t size) {
  t_malloc_info *env;

  env = set_up_environment();
  // ft_putstr(env->tiny.nothing);
  // ft_putstr(env->medium.nothing);
  // if (size < MEDIUM) {
  //   go_deal_with_small_or_medium()
  // } else {
  //   go_deal_with_large()
  // }

  return (mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE
					, -1, 0));
}
