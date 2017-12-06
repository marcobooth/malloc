#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

int main() {
	void *address;
	//malloc(11);
	//malloc(11);
	//malloc(13);
	//malloc(144);
	//malloc(1810);
	//malloc(12);
	address = malloc(9);
	free(address);
	show_alloc_mem();
}
