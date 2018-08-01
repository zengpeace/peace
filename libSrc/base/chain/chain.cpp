#include "base/chain/chain.h"


namespace peace 
{
namespace base 
{

RecvData *CreateChain(const int len)
{
	LOGD("prepare to create %d chain !\n", len);
	if (len < 1)
	{
		LOGD("param error ! length = %d\n", len);
		return NULL;
	}

	int i;
	RecvData *all = NULL;
	all = (RecvData *)malloc(len * sizeof(RecvData));
	if (!all)
	{
		LOGD("malloc fail !\n");
		return NULL;
	}
	for (i = 0; i < len - 1; i ++)
	{
		all[i].pNext = &all[i + 1];
	}
	all[len - 1].pNext = NULL;
	return &all[0];
}

void InsertHead(RecvData **dst, RecvData *src)
{
	RecvData *temp = src;

	if (temp == NULL) return;

	while (temp->pNext != NULL) temp = temp->pNext;

	temp->pNext = *dst;
	*dst = src;
}


void InsertTail(RecvData **dst, RecvData *src)
{
	RecvData *temp = *dst;

	if (temp == NULL)
	{
		*dst = src;
	}
	else
	{
		while (temp->pNext != NULL) temp = temp->pNext;
		temp->pNext = src;
	}
}

void InsertTailEx(RecvData **dst, RecvData *src, RecvData **dstLast)
{
	if (*dst == NULL)
	{
		*dst = src;
		*dstLast = src;
	}
	else
	{
		(*dstLast)->pNext = src;
		*dstLast = src;
	}
}

void InsertTailEx(RecvData **dst, RecvData **src, RecvData **dstLast, const int srcNum)
{
	/*char logBuf[256];
	int curSize, tmpSize;
	RecvData *tmp;
	curSize = snprintf(logBuf, 256, "%s begin:", __FUNCTION__);
	for(tmp = *dst; tmp; tmp = tmp->pNext, curSize += tmpSize)
	{
		tmpSize = snprintf(&logBuf[curSize], 256, "%p ", tmp);
	}
	snprintf(&logBuf[curSize], 256, "\n");
	LOGD("%s", logBuf);*/ 
	
	int srcStart = 0;
	if(*dst == NULL)
	{
		*dst = *src;
		(*dst)->pNext = NULL;
		*dstLast = *src;
		srcStart ++;
		
	}
	
	for(int i = srcStart; i < srcNum; i ++)
	{
		(*dstLast)->pNext = src[i];
		*dstLast = (*dstLast)->pNext;
	}

	(*dstLast)->pNext = NULL;

	/*curSize = snprintf(logBuf, 256, "%s end:", __FUNCTION__);
	for(tmp = *dst; tmp; tmp = tmp->pNext, curSize += tmpSize)
	{
		tmpSize = snprintf(&logBuf[curSize], 256, "%p ", tmp);
	}
	snprintf(&logBuf[curSize], 256, "\n");
	LOGD("%s", logBuf);*/ 
}


RecvData *GetHeadChain(RecvData **dst)
{
	RecvData *temp = *dst;

	if ((*dst) != NULL)
	{
		(*dst) = (*dst)->pNext;
		temp->pNext = NULL;
	}

	return temp;
}

int GetHeadChain(RecvData **dst, const int wantNum, RecvData **result)
{
	/*char logBuf[256];
	int curSize, tmpSize;
	RecvData *tmp;
	curSize = snprintf(logBuf, 256, "%s begin:", __FUNCTION__);
	for(tmp = *dst; tmp; tmp = tmp->pNext, curSize += tmpSize)
	{
		tmpSize = snprintf(&logBuf[curSize], 256, "%p ", tmp);
	}
	snprintf(&logBuf[curSize], 256, "\n");
	LOGD("%s", logBuf);*/ 

	int resultNum;
	for(resultNum = 0; resultNum < wantNum && (*dst); resultNum ++)
	{
		//LOGD("%d: %p,%p, %p,%p\n", resultNum, *dst, result[resultNum], dst, result);
		result[resultNum] = *dst;
		*dst = (*dst)->pNext;
		result[resultNum]->pNext = NULL;
	}

	/*curSize = snprintf(logBuf, 256, "%s end:", __FUNCTION__);
	for(tmp = *dst; tmp; tmp = tmp->pNext, curSize += tmpSize)
	{
		tmpSize = snprintf(&logBuf[curSize], 256, "%p ", tmp);
	}
	snprintf(&logBuf[curSize], 256, "\n");
	LOGD("%s", logBuf);*/ 

	return resultNum;
}

void RecoveryChain(RecvData *src, RecvData **recvDataUdp, pthread_mutex_t *LockChain)
{
	//LOGD("%s: %p,%p\n", __FUNCTION__, src, recvDataUdp);
	pthread_mutex_lock(LockChain);
	if (recvDataUdp)
	{
		InsertHead(recvDataUdp, src);
	}
	pthread_mutex_unlock(LockChain);
}

void ReleaseChain(RecvData **ppHead)
{
	if (!ppHead || !(*ppHead)) return;

	free(*ppHead);
	*ppHead = NULL;
}


} //namespace base 
} //namespace peace 

