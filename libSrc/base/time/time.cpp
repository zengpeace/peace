#include "time.h"


namespace peace 
{
namespace base 
{

unsigned int getCurMs()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	return (unsigned int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}



} //namespace base 
} //namespace peace 


