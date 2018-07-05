#ifndef _PEACE_BASE_THREAD_THREAD_H_
#define _PEACE_BASE_THREAD_THREAD_H_ 

#include "types.h"

namespace peace 
{
namespace base 
{

int threadCreate(pthread_t &pid, void*(*thread_callback)(void*), void *arg, const size_t stack_size);

int threadCreateSmall(pthread_t &pid, void*(*thread_callback)(void*), void *arg);
int threadCreateMiddle(pthread_t &pid, void*(*thread_callback)(void*), void *arg);
int threadCreateLarge(pthread_t &pid, void*(*thread_callback)(void*), void *arg);

void threadClose(pthread_t &pid);

} //namespace base
} //namespace peace




#endif

