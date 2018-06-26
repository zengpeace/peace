#ifndef _PEACE_BASE_THREAD_THREAD_H_
#define _PEACE_BASE_THREAD_THREAD_H_ 

#include "types.h"

namespace peace 
{
namespace base 
{

int threadCreate(pthread_t &pid, void*(*thread_callback)(void*), void *arg, const size_t stack_size);
void threadClose(pthread_t &pid);

} //namespace base
} //namespace peace




#endif

