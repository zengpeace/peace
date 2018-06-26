#include "thread.h"


namespace peace 
{
namespace base
{
 
int threadCreate(pthread_t &pid, void*(*thread_callback)(void*), void *arg, const size_t stack_size)
{
	if (!pid || stack_size < 4 * 1024)
	{
		LOGD("%s: para errror ! %ld,%p,%d\n", __FUNCTION__, pid, thread_callback, (int)stack_size);
		return -1;
	}

	size_t stacksize;
	pthread_attr_t attr, *set_attr;
	if (pthread_attr_init(&attr) != 0) LOGD("pthread_attr_init failure !\n");
	if (pthread_attr_getstacksize(&attr, &stacksize) != 0) LOGD("pthread_attr_getstacksize failure !\n");
	if (pthread_attr_setstacksize(&attr, stack_size) != 0) LOGD("pthread_attr_setstacksize failure !\n");
	if (pthread_attr_getstacksize(&attr, &stacksize) != 0) LOGD("pthread_attr_getstacksize failure !\n");
	set_attr = &attr;

	return pthread_create(&pid, set_attr, thread_callback, arg);
}

void threadClose(pthread_t &pid)
{
	if(pid > 0)
	{
		pthread_join(pid, NULL);
		pid = 0;
	}
}
 
} //namespace base
} //namespace peace

