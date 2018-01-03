#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

int main() {
	void *address;
	void *address2;
	void *address3;
	void *address4;
	//malloc(11);
	//malloc(11);
	//malloc(13);
	//malloc(144);
	//malloc(1810);
	//malloc(12);
	ft_putstr("------- START ---------- \n");
	address = malloc(90);
	ft_putstr("finished the call\n");
	free(address);
	ft_putstr("------- END ---------- \n");
	// ft_putstr("------- START2 ---------- \n");
	// address2 = malloc(11);
	// ft_putstr("finished the call\n");
	// free(address2);
	// ft_putstr("------- END2 ---------- \n");
	// ft_putstr("------- START3 ---------- \n");
	// address3 = malloc(4);
	// ft_putstr("finished the call\n");
	// free(address3);
	// free(address4);
	// ft_putstr("------- END3 ---------- \n");
	// ft_putstr("About to show the allocated memory\n");
	// show_alloc_mem();
}
