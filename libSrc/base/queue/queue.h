#ifndef _PEACE_BASE_QUEUE_QUEUE_H_
#define _PEACE_BASE_QUEUE_QUEUE_H_

#include "types.h"

namespace peace 
{
namespace base 
{

int queueInit(BlockInfo *pBlockInfo, const int blockNum, const int blockTotalSize);
int queuePush(BlockInfo *pBlockInfo, const unsigned char *pData, const int iSize, const unsigned char *pFrontData, const int iFrontSize);

template<typename T>
int queuePopInternal(BlockInfo *pBlockInfo, T pFunc, void* arg);

template<typename T>
int queuePop(BlockInfo *pBlockInfo, T pFunc, void* arg, bool(*loopConditionFunc)(void *arg), void* argTimeout, const int timeOut);

void queueDestroy(BlockInfo *pBlockInfo);

} //namespace base
} //namespace peace

#endif

