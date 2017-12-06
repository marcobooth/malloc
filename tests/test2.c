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

int main(void)
{
	int a;
	uintmax_t b;

	b = (uintmax_t)&a;
	uintptr_t uip = (uintptr_t) ((void*) &a);
	printf("address of a = 0x%"PRIXPTR, uip);
	ft_putstr("\n");
	int i;
	i = 0;
	while (i < 5) {
		ft_putnbr(b % 16);
		ft_putstr(".");
		b /= 16;
		i++;
	}
	ft_putstr("finished this thing");
}
