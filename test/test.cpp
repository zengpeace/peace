#include "peaceInterface.h"



int main()
{
	unsigned char buf[99] = {48};
	unsigned char buf2[99] = {49};
	for(int i = 0; i < 10; i ++)
	{
		fileSimpleWrite(buf, 98, "test1.txt");
		fileSimpleWrite(buf2, 98, "test2.txt");
	}

	return 0;
}

