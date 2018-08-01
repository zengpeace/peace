#ifndef _PEACE_BASE_MEMORY_ALLOCATE_H_
#define _PEACE_BASE_MEMORY_ALLOCATE_H_ 

#include "types.h"

namespace peace 
{
namespace base 
{
	
void** newPP(const int num, const int eachByteSize = 0);
void deletePP(void** &PP, const int num = 0);

}
}
#endif


