#ifndef _PEACE_BASE_QUEUE_QUEUE_H_
#define _PEACE_BASE_QUEUE_QUEUE_H_

#include "base/commonInternal.h"

namespace peace {
namespace base {

typedef struct
{
	sem_t m_Semaphore;
	pthread_mutex_t m_Lock;
	BufferInfo *m_Push;
	BufferInfo *m_Pop;
	BufferInfo *m_pInfo;
	unsigned char *m_pData;
	unsigned char *m_pCurr;
	int m_nInfoSize;
	int m_nDataSize;
}BlockInfo;














} //namespace base
} //namespace peace

#endif

