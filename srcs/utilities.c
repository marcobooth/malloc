#include "malloc.h"

void print_pointer(void *ptr) {
	int i;
  uintmax_t b;
	char pointer_address[13] = "0123456789012";

  b = (uintmax_t)ptr;

	i = 11;
	while (i >= 0) {
		if ((b % 16) < 10)
			pointer_address[i] = '0' + (b % 16);
		else
			pointer_address[i] = 'a' + ((b % 16) - 10);
		b /= 16;
		i--;
	}
	pointer_address[12] = '\0';
	ft_putstr("0x");
	ft_putstr(pointer_address);
}

void print_maps(t_list *maps, size_t map_size) {
	t_map_info *map_info;

	map_info = (t_map_info*)maps;
	while (map_info) {
		print_pointer(map_info);
		ft_putstr(" - ");
		print_pointer(map_info + map_size);
		ft_putstr(" (");
		ft_putnbr(map_info->allocations);
		ft_putstr(" allocation)\n");
		map_info = (t_map_info*)map_info->list.next;
	}
}

void print_allocations(t_list *allocations) {
	t_alloc_info *alloc_info;

	alloc_info = (t_alloc_info*)allocations;
	while(alloc_info) {
		// if type if t_alloc_info and you add 32, the compiler adds 32 t_alloc_infos
		// either add 1 (t_alloc_info)
		print_pointer((alloc_info + 1));
		ft_putstr(" - ");
		// or add to void pointer
		print_pointer((void*)alloc_info + sizeof(t_alloc_info) + alloc_info->size);
		ft_putstr(" : ");
		ft_putnbr(alloc_info->size);
		ft_putstr(" bytes\n");
		alloc_info = (t_alloc_info*)alloc_info->list.next;
	}
}

void      show_alloc_mem() {
	if (g_malloc_info == NULL) {
		ft_putstr("No map information available\n");
		return;
	}

	ft_putstr("---------- SHOW ALLOCATED MEMORY ----------\n");

	if (g_malloc_info->tiny.maps != NULL) {
		ft_putstr("TINY maps:\n");
		// should I be giving the address here, make a difference using the direct value?
		print_maps(g_malloc_info->tiny.maps, g_malloc_info->tiny.env_size);
	}
  if (g_malloc_info->tiny.allocations != NULL) {
    ft_putstr("TINY allocations\n");
		print_allocations(g_malloc_info->tiny.allocations);
  }
	if (g_malloc_info->small.maps != NULL) {
		ft_putstr("SMALL maps:\n");
		print_maps(g_malloc_info->small.maps, g_malloc_info->small.env_size);
	}
	if (g_malloc_info->small.allocations != NULL) {
		ft_putstr("SMALL allocations\n");
		print_allocations(g_malloc_info->small.allocations);
	}
	if (g_malloc_info->large_maps != NULL) {
		ft_putstr("LARGE allocations\n");
		print_allocations(g_malloc_info->large_maps);
	}
}
