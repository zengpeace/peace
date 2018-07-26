#include "allocate.h"

namespace peace
{
namespace base
{

void newPP(void** &pp, const int num, const int eachByteSize)
{
	if(num <= 0)
	{
		LOGD("%s:num error ! %d\n", __FUNCTION__, num);
		return;
	}	

	pp = new void*[num];
	if(!pp)
	{
		LOGD("new first fail !\n");
		return;
	}

	unsigned char *p;
	for(int i = 0; i < num; i ++)
	{
		if(eachByteSize > 0)
		{
			p = new unsigned char[eachByteSize];
			if(!p)
			{
				LOGD("new unsigned char %d fail !\n", eachByteSize);
				delete[] pp;
				pp = NULL;
				return;
			}

			pp[i] = (void*)p;
		}
		else 
		{
			pp[i] = NULL;
		}
	}
}

void deletePP(void** &pp, const int num)
{
	/*for(int i = 0; i < num; i ++)
	{
		delete[] pp[i];
		pp[i] = NULL;
	}*/
	
	delete[] pp;
	pp = NULL;
}

}
}

