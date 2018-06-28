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

void ReleaseChain(RecvData **ppHead)
{
	if (!ppHead || !(*ppHead)) return;

	free(*ppHead);
	*ppHead = NULL;
}


} //namespace base 
} //namespace peace 

