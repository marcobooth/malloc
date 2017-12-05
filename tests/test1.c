#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

int main() {
	//malloc(11);
	malloc(11);
	malloc(13);
	//malloc(144);
	//malloc(1810);
	malloc(12);
	malloc(120);
	show_alloc_mem();
}
