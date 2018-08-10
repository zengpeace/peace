//#include <stdio.h>
#include "jemalloc.h"


int main()
{
	int *a = (int*)malloc(sizeof(int));
	*a = 2;

	int b = 3;
	b += *a;
	return 0;
}

