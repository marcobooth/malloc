#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

int main() {
	void *address;
	void *address2;
	void *address3;
	//malloc(11);
	//malloc(11);
	//malloc(13);
	//malloc(144);
	//malloc(1810);
	//malloc(12);
	ft_putstr("------- START ---------- \n");
	address = malloc(900);
	ft_putstr("finished the call\n");
	free(address);
	ft_putstr("------- END ---------- \n");
	ft_putstr("------- START2 ---------- \n");
	address2 = malloc(1100);
	ft_putstr("finished the call\n");
	free(address2);
	ft_putstr("------- END2 ---------- \n");
	ft_putstr("------- START3 ---------- \n");
	address3 = malloc(4);
	ft_putstr("finished the call\n");
	free(address3);
	ft_putstr("------- END3 ---------- \n");
	// ft_putstr("About to show the allocated memory\n");
	// show_alloc_mem();
}
