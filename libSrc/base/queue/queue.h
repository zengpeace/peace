#ifndef _PEACE_BASE_QUEUE_QUEUE_H_
#define _PEACE_BASE_QUEUE_QUEUE_H_

#include "types.h"

namespace peace 
{
void queuet();
namespace base 
{

void queuet2();

int QueueInit(BlockInfo *pBlockInfo, const int blockNum, const int blockTotalSize);
int QueuePush(BlockInfo *pBlockInfo, const unsigned char *pData, const int iSize, const unsigned char *pFrontData, const int iFrontSize);

template<typename T>
int QueuePopInternal(BlockInfo *pBlockInfo, const T& pFunc, void* arg);

template<typename T>
int QueuePop(BlockInfo *pBlockInfo, const T& pFunc, void* arg, int(*loopConditionFunc)(void *arg), void* argTimeout, const int timeOut);


} //namespace base
} //namespace peace

#endif

