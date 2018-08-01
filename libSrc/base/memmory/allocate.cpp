#include "allocate.h"

namespace peace
{
namespace base
{

void** newPP(const int num, const int eachByteSize)
{
	if(num <= 0)
	{
		LOGD("%s:num error ! %d\n", __FUNCTION__, num);
		return NULL;
	}	

	void** pp = new void*[num];
	if(!pp)
	{
		LOGD("new first fail !\n");
		return NULL;
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
				break;
			}

			pp[i] = (void*)p;
		}
		else 
		{
			pp[i] = NULL;
		}
	}

	return pp;
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

