#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "malloc.h"
#include <string.h>

int hex_to_int(char c){
	int first = c / 16 - 3;
	int second = c % 16;
	int result = first*10 + second;
	if(result > 9) result--;
	return result;
}

int hex_to_ascii(char c, char d){
	int high = hex_to_int(c) * 16;
	int low = hex_to_int(d);
	return high+low;
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
	ft_putstr("\n");
}

int   compare_pointers(void *p1, void *p2) {
  ft_putstr("p1: ");
  print_pointer(p1);
  ft_putstr("p2: ");
  print_pointer(p2);
  if (p1 == p2) {
    return (TRUE);
  }

  return (FALSE);
}

int main(void)
{
	int a;
	int b;
	void *hello;

	hello = &a;
	a = compare_pointers(hello, &b);
	// print_pointer(hello);
	printf("Returned value: %i\n", a);
	ft_putstr("\n");
}
