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
int queuePopInternal(BlockInfo *pBlockInfo, void(*pFunc)(const unsigned char*, const int, void*), void* arg);
int queuePop(BlockInfo *pBlockInfo, void(*pFunc)(const unsigned char*, const int, void*), void* arg, bool(*loopConditionFunc)(void *arg), void* argTimeout, const int timeout);

//thread
int threadCreate(pthread_t &pid, void*(*threadCallback)(void*), void *arg, const size_t stackSize);
int threadCreateSmall(pthread_t &pid, void*(*threadCallback)(void*), void *arg);
int threadCreateMiddle(pthread_t &pid, void*(*threadCallback)(void*), void *arg);
int threadCreateLarge(pthread_t &pid, void*(*threadCallback)(void*), void *arg);
void threadClose(pthread_t &pid);

//file 
void fileSimpleWrite(const unsigned char *data, const int size, const char *fileAbsName);
void fileSimpleClose(const char *fileAbsName);


//chain
RecvData *chainCreate(const int len);
void chainInsertHead(RecvData **dst, RecvData *src);
void chainInsertTail(RecvData **dst, RecvData *src);
void chainInsertTailEx(RecvData **dst, RecvData *src, RecvData **dstLast);
void chainInsertTailEx(RecvData **dst, RecvData **src, RecvData **dstLast, const int srcNum);
RecvData *chainGetHead(RecvData **dst);
int chainGetHead(RecvData **dst, const int wantNum, RecvData **result);
void chainRecovery(RecvData *src, RecvData *recvDataUdp, pthread_mutex_t LockChain);
void chainRelease(RecvData **ppHead);


//time
unsigned int getCurMs();


//memmory
void** newPP(const int num, const int eachByteSize = 0);
void deletePP(void** &pp, const int num = 0);
/*************************************************/


/**************** net ****************************/ 
void* netCreate(const char *type, void* arg, const bool useMmsg = false);
void* udpServerCreate(void* arg);
void* udpClientCreate(void* arg);
void netDestroy(void *base);
int netSetChainSize(void *base, const int size); //default value is CHAIN_SIZE
void netSetUseSendThread(void *base);
int netRegisterTcpBusFunc(void *base, const TcpBusinessDealFuncType pFunc);
int netRegisterUdpBusFunc(void *base, const UdpBusinessDealFuncType pFunc);
int netStart(void*base, const char *ip, const int port = 0, const int sockSendBufSize = gSockBufSize/2, const int sockRecvBufSize = gSockBufSize/2);
int netStop(void *base);
int netSend(void *base, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr);
int netSend(void *base, const unsigned char *data, const int dataSize, const int sock);
int netSend(void *base, const unsigned char *data, const int dataSize);
/*************************************************/ 


/**************** media ************************/ 
void mediaReadSplitH264(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize);
void mediaReadSplitAAC(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize);
/***********************************************/ 


/**************** other ************************/ 
void* mmsgRecvInit(const char *ip, const int port);
int mmsgRecvDo(void* recv);
void mmsgRecvExit(void *recv);
/***********************************************/ 

/*
#ifdef __cplusplus
}
#endif  
*/

#endif


