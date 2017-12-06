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
    // printf("g_malloc_info: %p\n", g_malloc_info);
    // printf("g_malloc_info->tiny: %p\n", &g_malloc_info->tiny);
    // printf("g_malloc_info->small: %p\n", &g_malloc_info->small);
  }

  return (g_malloc_info);
}

void		list_push_back(t_list **begin_list, void *data, t_list *new_one)
{
  // printf("next: %p\n", env_info->next_available_location);
  //only using this as a list of addresses
	new_one->next = NULL;
  new_one->data = data;
	if (*begin_list == NULL) {
    *begin_list = new_one;
  }
  else {
    ft_list_find_end(*begin_list)->next = new_one;
  }
}

// t_list		*ft_list_find_end(t_list *list)
// {
// 	if (list->next == NULL)
// 		return (list);
// 	return (ft_list_find_end(list->next));
// }

void      show_alloc_mem() {
  t_map_info *a;
  printf("\n Maps \n");
  printf("TINY\n");
  if (g_malloc_info->tiny.allocations == NULL) {
    ft_putstr("equal to NULL, returning\n");
    return;
  }
  // ft_putstr("not returning\n");
  a = (t_map_info*)g_malloc_info->tiny.allocations;
  while (a != NULL) {
    ft_putnbr(a->allocations);
    ft_putstr("allocated\n");
    a = (t_map_info*)a->list.next;
  }
}

void *tiny_or_small(size_t size, t_env_info *env_info) {
  void *map;
  void *new_memory;
  t_alloc_info *alloc_info;

  if ( !env_info->next_available_location
    || !(env_info->next_available_location + sizeof(t_map_info) + size < env_info->end_location)
    ) {
      map = get_mmap(env_info->env_size);
      // printf("map: %p\n", map);
      env_info->next_available_location = map + sizeof(t_map_info);
      env_info->end_location = map + env_info->env_size;
      env_info->current_map = (t_map_info*)map;

      // Data doesn't need anything, we only need the list of addresses
      // printf("size of t_map_info: %zu\n", sizeof(t_map_info));
      // printf("env_info: %p\n", env_info);
      // printf("env_info->maps: %p\n", env_info->maps);
      // printf("env_info->current_map: %p\n", env_info->current_map);
      // printf("env_info->current_map->list: %p\n", (void *)&env_info->current_map->list);
      // printf("&env_info->current_map->allocations: %p\n", &env_info->current_map->allocations);

      // env_info->current_map->list = map;
      list_push_back((t_list**)&env_info->maps, NULL, &env_info->current_map->list);

      // printf("env_info: %p\n", env_info);
      // printf("env_info->maps: %p\n", env_info->maps);
      // printf("env_info->current_map: %p\n", env_info->current_map);
      // printf("env_info->current_map->list: %p\n", (void *)&env_info->current_map->list);
      // env_info->current_map->allocations = 0;
  }

  alloc_info = (t_alloc_info*)env_info->next_available_location;
  list_push_back(&env_info->allocations, &alloc_info->list, &alloc_info->list);
  alloc_info->size = size;
  alloc_info->map_of_this_allocation = env_info->current_map;
  new_memory = env_info->next_available_location + sizeof(t_alloc_info);
  env_info->next_available_location = env_info->next_available_location
                                      + sizeof(t_alloc_info)
                                      + size;
  // return env_info->next_available_location;
  return new_memory;
}

int   compare_pointers(void *p1, void *p2) {
  if (p1 == p2) {
    return (TRUE);
  }

  return (FALSE);
}

void       free(void *ptr) {
  t_alloc_info *allocation;

  allocation = (t_alloc_info*)ft_list_find(g_malloc_info->tiny.allocations, ptr, &compare_pointers);
  if (allocation == NULL) {
    // ft_putstr("\n equals NULL \n");
  } else {
    ft_putstr("\nnot equal to NULL - ");
    ft_putnbr(allocation->size);
    ft_putstr(" bytes \n");
  }

}

void *malloc(size_t size) {
  t_malloc_info *env;
  void          *memory;


  env = set_up_environment();
  if (size < TINY) {
    // ft_putstr("I am in tiny");
    ft_putnbr(size);
    ft_putstr(" bytes\n");
    return tiny_or_small(size, &env->tiny);
  }
  // else if (size < SMALL) {
  //   memory = tiny_or_small(size, env->small);
  // } else {
  memory = get_mmap(size);
  // }

  return (memory);
}

// printf("\nNumber: %zu\n", env_info->env_size);
// printf("Size of thing %zu\n", sizeof(t_map_info));
// printf("next: %p\n", map);
// printf("next: %p\n", env_info->next_available_location);
// printf("%p\n", env_info->end_location);
// printf("current: %p\n", map);
// printf("next: %p\n", env_info->next_available_location);
