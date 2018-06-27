#include "peaceInterface.h"
#include "peace.h"

/**************** base **************************/
//queue
int queueInit(BlockInfo *pBlockInfo, const int blockNum, const int blockTotalSize)
{
	return peace::base::QueueInit(pBlockInfo, blockNum, blockTotalSize);
}

int queuePush(BlockInfo *pBlockInfo, const unsigned char *pData, const int iSize, const unsigned char *pFrontData, const int iFrontSize)
{
	return peace::base::QueuePush(pBlockInfo, pData, iSize, pFrontData, iFrontSize);
}

template<typename T>
int queuePopInternal(BlockInfo *pBlockInfo, const T& pFunc, void* arg)
{
	return peace::base::QueuePopInternal(pBlockInfo, pFunc, arg);
}

template<typename T>
int queuePop(BlockInfo *pBlockInfo, const T& pFunc, void* arg, int(*loopConditionFunc)(void *arg), void* argTimeout, const int timeout)
{
	return peace::base::QueuePop(pBlockInfo, pFunc, arg, loopConditionFunc, argTimeout, timeout);
}

//thread
int threadCreate(pthread_t &pid, void*(*threadCallback)(void*), void *arg, const size_t stackSize)
{
	return peace::base::threadCreate(pid, threadCallback, arg, stackSize);
}

void threadClose(pthread_t &pid)
{
	return peace::base::threadClose(pid);
}

//file 
void fileSimpleWrite(const unsigned char *data, const int size, const char *fileAbsName)
{
	return peace::base::fileSimpleWrite(data, size, fileAbsName);
}

void fileSimpleClose(const char *fileAbsName)
{
	return peace::base::fileSimpleClose(fileAbsName);
}

/**************************************************/ 




