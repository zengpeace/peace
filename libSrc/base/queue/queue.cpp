#include "queue.h"

namespace peace {
namespace base {

int queueInit(BlockInfo *pBlockInfo, const int blockNum, const int blockTotalSize)
{
	int nInfoSize = blockNum;
	int nDataSize = blockTotalSize;
	if(!pBlockInfo || blockNum <= 0 || blockTotalSize <= 0)
	{
		LOGD("%s:para error ! %p, %d, %d\n", __FUNCTION__, pBlockInfo, blockNum, blockTotalSize);
		return -1;				
	}

	if (sem_init(&(pBlockInfo->m_Semaphore), 0, 0) != 0)
	{
		LOGD("sem_init failure {%s(%d)}\n", __FILE__, __LINE__);
		return -1;
	}

	if (pthread_mutex_init(&pBlockInfo->m_Lock, NULL) != 0)
	{
		LOGD("pthread_mutex_init failure {%s(%d)}\n", __FILE__, __LINE__);
		return -2;
	}

	if ((pBlockInfo->m_pInfo = (BufferInfo*)malloc(nInfoSize * sizeof(BufferInfo) + nDataSize)) == NULL)
	{
		LOGD("sem_init failure {%s(%d)}\n", __FILE__, __LINE__);
		return -4;
	}
    memset(pBlockInfo->m_pInfo, 0, nInfoSize * sizeof(BufferInfo) + nDataSize);

	pBlockInfo->m_nInfoSize = nInfoSize;
	pBlockInfo->m_nDataSize = nDataSize;
	pBlockInfo->m_pData = (unsigned char *)(pBlockInfo->m_pInfo + pBlockInfo->m_nInfoSize);

	pBlockInfo->m_Push = pBlockInfo->m_Pop = pBlockInfo->m_pInfo;
	pBlockInfo->m_pCurr = pBlockInfo->m_pData;

	BufferInfo *pTempBufInfo = pBlockInfo->m_pInfo;

	for (int i = 0; i < pBlockInfo->m_nInfoSize; i++)
	{
		if (i == (pBlockInfo->m_nInfoSize - 1))
			pTempBufInfo->pNext = pBlockInfo->m_pInfo;
		else
			pTempBufInfo->pNext = pTempBufInfo + 1;

			pTempBufInfo++;
	}

	return 0;
}

int queuePush(BlockInfo *pBlockInfo, const unsigned char *pData, const int iSize, const unsigned char *pFrontData, const int iFrontSize)
{
	int ret = 0;
	BufferInfo *Pop;

	pthread_mutex_lock(&(pBlockInfo->m_Lock));

	if (iSize + iFrontSize > pBlockInfo->m_nDataSize)
	{
		ret = -1;
		pthread_mutex_unlock(&(pBlockInfo->m_Lock));
		return ret;
	}

	if (pBlockInfo->m_Push->nFlag != 0)
	{
		ret = -2;
		pthread_mutex_unlock(&(pBlockInfo->m_Lock));
		return ret;
	}

	if (iSize + iFrontSize> (pBlockInfo->m_pData + pBlockInfo->m_nDataSize - pBlockInfo->m_pCurr))
	{
		pBlockInfo->m_pCurr = pBlockInfo->m_pData;
	}

	Pop = pBlockInfo->m_Pop;

	while (Pop->nFlag)
	{
		if (Pop->pData >= pBlockInfo->m_pCurr)
		{
			if ((Pop->pData - pBlockInfo->m_pCurr) < iSize + iFrontSize)
			{
				ret = -3;
				pthread_mutex_unlock(&(pBlockInfo->m_Lock));
				return ret;
			}

		}
		Pop = Pop->pNext;
	}

	if (pFrontData && iFrontSize > 0)
	{
		memcpy(pBlockInfo->m_pCurr, pFrontData, iFrontSize);
	}

	if (pData && iSize > 0)
	{
		memcpy(pBlockInfo->m_pCurr + iFrontSize, pData, iSize);
	}

	pBlockInfo->m_Push->pData = pBlockInfo->m_pCurr;
	pBlockInfo->m_Push->nSize = iSize + iFrontSize;
	pBlockInfo->m_Push->nFlag = 1;
	pBlockInfo->m_Push = pBlockInfo->m_Push->pNext;

	pBlockInfo->m_pCurr += (iSize + iFrontSize);

	sem_post(&(pBlockInfo->m_Semaphore));

	pthread_mutex_unlock(&(pBlockInfo->m_Lock));

	return ret;
}

template <typename T>
int queuePopInternal(BlockInfo *pBlockInfo, const T& pFunc, void* arg)
{
	if (pBlockInfo == NULL || pBlockInfo->m_Pop == NULL)
	{
		LOGD("%s: para error ! pBlockInfo=%p\n", __FUNCTION__, pBlockInfo);
		return -1;
	}

	while (pBlockInfo && pBlockInfo->m_Pop && pBlockInfo->m_Pop->nFlag)
	{
		pFunc(pBlockInfo->m_Pop->pData, pBlockInfo->m_Pop->nSize, arg);
		pthread_mutex_lock(&(pBlockInfo->m_Lock));
		pBlockInfo->m_Pop->nFlag = 0;
		pBlockInfo->m_Pop = pBlockInfo->m_Pop->pNext;
		pthread_mutex_unlock(&(pBlockInfo->m_Lock));
	}

	return 0;
}

int queuePop(BlockInfo *pBlockInfo, const T& pFunc, void* arg, int(*loopConditionFunc)(void *arg), void* argTimeout, const int timeOut)
{
	struct timespec ts;
	struct timeval  tv;
	while (loopConditionFunc(argTimeout))
	{
		gettimeofday(&tv, NULL);
		ts.tv_sec = tv.tv_sec + timeOut;
		ts.tv_nsec = tv.tv_usec * 1000;
		sem_timedwait(&(pBlockInfo->m_Semaphore), &ts);

		queuePop(pBlockInfo, pFunc, arg);
	}

	return 0;
}

} //namespace base
} //namespace peace









} //namespace base
} //namespace peace

