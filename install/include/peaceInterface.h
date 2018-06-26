#ifndef _PEACE_PEACE_INTERFACE_H_
#define _PEACE_PEACE_INTERFACE_H_ 


#include "types.h"


/*
#ifdef __cplusplus
extern "C"
{
#endif
*/ 

/**************** base **************************/
//queue
int queueInit(BlockInfo *pBlockInfo, const int blockNum, const int blockTotalSize);
int queuePush(BlockInfo *pBlockInfo, const unsigned char *pData, const int iSize, const unsigned char *pFrontData, const int iFrontSize);
template<typename T>
int queuePopInternal(BlockInfo *pBlockInfo, const T& pFunc, void* arg);
template<typename T>
int queuePop(BlockInfo *pBlockInfo, const T& pFunc, void* arg, int(*loopConditionFunc)(void *arg), void* argTimeout, const int timeout);

//thread
int threadCreate(pthread_t &pid, void*(*threadCallback)(void*), void *arg, const size_t stackSize);
void threadClose(pthread_t &pid);

//file 
void fileSimpleWrite(const unsigned char *data, const int size, const char *fileAbsName);
void fileSimpleClose(const char *fileAbsName);
/*************************************************/


/**************** net ****************************/ 












/*************************************************/ 

/*
#ifdef __cplusplus
}
#endif 
*/ 

#endif




