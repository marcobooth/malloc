#include "malloc.h"

void *get_mmap(size_t size) {
  // mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
  // PROT_READ   Pages may be read
  // PROT_WRITE  Pages may be written
  // MAP_ANON          Map anonymous memory not associated with any specific file
  // MAP_PRIVATE       Modifications are private (copy-on-write)
  return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
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

void print_list(t_list *list) {
  int i;

  i = 0;
  while (list) {
    ft_putstr("List number is ");
    ft_putnbr(i);
    ft_putstr("\n");
    print_pointer(list);
		ft_putstr("\n");
    list = list->next;
    i += 1;
  }
}

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
