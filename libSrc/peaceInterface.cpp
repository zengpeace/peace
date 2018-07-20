#include "peaceInterface.h"
#include "peace.h"

/**************** base **************************/
//queue
int queueInit(BlockInfo *pBlockInfo, const int blockNum, const int blockTotalSize)
{
	return peace::base::queueInit(pBlockInfo, blockNum, blockTotalSize);
}

int queuePush(BlockInfo *pBlockInfo, const unsigned char *pData, const int iSize, const unsigned char *pFrontData, const int iFrontSize)
{
	return peace::base::queuePush(pBlockInfo, pData, iSize, pFrontData, iFrontSize);
}

int queuePopInternal(BlockInfo *pBlockInfo, void(*pFunc)(const unsigned char*, const int, void*), void* arg)
{
	return peace::base::queuePopInternal(pBlockInfo, pFunc, arg);
}

int queuePop(BlockInfo *pBlockInfo, void(*pFunc)(const unsigned char*, const int, void*), void* arg, bool(*loopConditionFunc)(void *arg), void* argTimeout, const int timeout)
{
	return peace::base::queuePop(pBlockInfo, pFunc, arg, loopConditionFunc, argTimeout, timeout);
}


//thread
int threadCreate(pthread_t &pid, void*(*threadCallback)(void*), void *arg, const size_t stackSize)
{
	return peace::base::threadCreate(pid, threadCallback, arg, stackSize);
}

int threadCreateSmall(pthread_t &pid, void*(*threadCallback)(void*), void *arg)
{
	return peace::base::threadCreateSmall(pid, threadCallback, arg);
}

int threadCreateMiddle(pthread_t &pid, void*(*threadCallback)(void*), void *arg)
{
	return peace::base::threadCreateMiddle(pid, threadCallback, arg);
}

int threadCreateLarge(pthread_t &pid, void*(*threadCallback)(void*), void *arg)
{
	return peace::base::threadCreateLarge(pid, threadCallback, arg);
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

void readSplitH264(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize)	
{
	return peace::base::fileReadSplitH264(fileAbsName, dealFunc, arg, readBuf, readBufSize);
}

void readSplitAAC(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize)	
{
	return peace::base::fileReadSplitAAC(fileAbsName, dealFunc, arg, readBuf, readBufSize);
}


//chain
RecvData *chainCreate(const int len)
{
	return peace::base::CreateChain(len);
}

void chainInsertHead(RecvData **dst, RecvData *src)
{
	return peace::base::InsertHead(dst, src);
}

void chainInsertTail(RecvData **dst, RecvData *src)
{
	return peace::base::InsertTail(dst, src);
}

void chainInsertTailEx(RecvData **dst, RecvData *src, RecvData **dstLast)
{
	return peace::base::InsertTailEx(dst, src, dstLast);
}

RecvData *chainGetHead(RecvData **dst)
{
	return peace::base::GetHeadChain(dst);
}

void chainRecovery(RecvData *src, RecvData *recvDataUdp, pthread_mutex_t LockChain)
{
	return peace::base::RecoveryChain(src, recvDataUdp, LockChain);
}

void chainRelease(RecvData **ppHead)
{
	return peace::base::ReleaseChain(ppHead);
}


//time
unsigned int getCurMs()
{
	return peace::base::getCurMs();
}

/**************************************************/ 



/************************ net *********************/ 
void* netCreate(const char *type, void *arg)
{
	if(!type)
	{
		return NULL;
	}

	peace::net::NetBase::NetType t;
	if(strcmp(type, "udpServer") == 0)
	{
		t = peace::net::NetBase::eNetUdpServer;
	}
	else if(strcmp(type, "udpClient") == 0)
	{
		t = peace::net::NetBase::eNetUdpClient;
	}
	else 
	{
		return NULL;
	}

	peace::net::NetBase *s = peace::net::NetBase::create(t, arg);
	if(!s)
	{
		LOGD("new netBase fail ! t=%u\n", (unsigned int)t);
		return NULL;
	}

	int ret;
	ret = s->init();
	if(ret < 0)
	{
		LOGD("netBase init fail ! %d, t = %u\n", ret, (unsigned int)t);
		return NULL;
	}

	return (void*)s;
}

void* udpServerCreate()
{
	return netCreate("udpServer");
}

void* udpClientCreate()
{
	return netCreate("udpClient");
}

void netDestroy(void *base)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base; 
	if(b == NULL)
	{
		LOGD("%s fail !\n", __FUNCTION__);
		return;
	}

	b->exit();
	delete b;	
}

int netSetChainSize(void *base, const int size) //default value is CHAIN_SIZE
{
	peace::net::NetBase *b = (peace::net::NetBase*)base; 
	if(b == NULL)
	{
		LOGD("%s fail !\n", __FUNCTION__);
		return -1;
	}

	b->setChainSize(size);
	return 0;
}

void netSetUseSendThread(void *base)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base; 
	if(b == NULL)
	{
		LOGD("%s fail !\n", __FUNCTION__);
		return;
	}

	b->setUseSendThread();
}

int netRegisterTcpBusFunc(void *base, const TcpBusinessDealFuncType pFunc)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base; 
	if(b == NULL)
	{
		LOGD("%s fail !\n", __FUNCTION__);
		return -1;
	}

	b->registerTcpBusinessDealFunc(pFunc);
	return 0;
}

int netRegisterUdpBusFunc(void *base, const UdpBusinessDealFuncType pFunc)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base; 
	if(b == NULL)
	{
		LOGD("%s fail !\n", __FUNCTION__);
		return -1;
	}

	b->registerUdpBusinessDealFunc(pFunc);
	return 0;
}

int netStart(void*base, const char *ip, const int port, const int sockSendBufSize, const int sockRecvBufSize)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base;
	if(b == NULL)
	{
		LOGD("%s fail ! base is NULL !\n", __FUNCTION__);
		return -1;
	}

	return b->start(ip, port, sockSendBufSize, sockRecvBufSize);
}

int netStop(void *base)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base;
	if(b == NULL)
	{
		LOGD("%s fail ! base is NULL !\n", __FUNCTION__);
		return -1;
	}
	
	b->stop();
	return 0;
}

int netSend(void *base, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base;
	if(b == NULL)
	{
		LOGD("%s fail ! base is NULL !\n", __FUNCTION__);
		return -1;
	}
		
	return b->send(data, dataSize, peerAddr);
}

int netSend(void *base, const unsigned char *data, const int dataSize, const int sock)
{
	return 0;
}

int netSend(void *base, const unsigned char *data, const int dataSize)
{
	peace::net::NetBase *b = (peace::net::NetBase*)base;
	if(b == NULL)
	{
		LOGD("%s fail ! base is NULL !\n", __FUNCTION__);
		return -1;
	}
	
	return b->send(data, dataSize);
}



/***************************************************/




