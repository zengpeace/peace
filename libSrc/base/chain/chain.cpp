#include "base/chain/chain.h"


namespace peace 
{
namespace base 
{

RecvData *CreateChain(const int len)
{
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
	if(*dst == NULL)
	{
		*dst = *src;
		*dstLast = *src;
	}
	else 
	{
		for(int i = 0; i < srcNum; i ++)
		{
			(*dstLast)->pNext = src[i];
			*dstLast = src[i];	
		}
	}
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
	int resultNum;
	*result = *dst;
	for(resultNum = 0; *dst; *dst = (*dst)->pNext, resultNum ++)
	{
		result[resultNum] = *dst;
		result[resultNum]->pNext = NULL;
	}

	return resultNum;
}

void RecoveryChain(RecvData *src, RecvData *recvDataUdp, pthread_mutex_t LockChain)
{
	pthread_mutex_lock(&(LockChain));
	if (recvDataUdp)
	{
		InsertHead(&recvDataUdp, src);
	}
	pthread_mutex_unlock(&(LockChain));
}

void ReleaseChain(RecvData **ppHead)
{
	if (!ppHead || !(*ppHead)) return;

	free(*ppHead);
	*ppHead = NULL;
}


} //namespace base 
} //namespace peace 

