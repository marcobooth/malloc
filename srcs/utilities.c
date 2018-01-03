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
  ft_putstr("\n");
}

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
