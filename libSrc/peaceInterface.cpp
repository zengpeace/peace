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

void chainInsertTailEx(RecvData **dst, RecvData **src, RecvData **dstLast, const int srcNum)
{
	return peace::base::InsertTailEx(dst, src, dstLast, srcNum);
}

RecvData *chainGetHead(RecvData **dst)
{
	return peace::base::GetHeadChain(dst);
}

int chainGetHead(RecvData **dst, const int wantNum, RecvData **result)
{
	return peace::base::GetHeadChain(dst, wantNum, result);
}

void chainRecovery(RecvData *src, RecvData **recvDataUdp, pthread_mutex_t *LockChain)
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

//memory

void** newPP(const int num, const int eachByteSize)
{
	return peace::base::newPP(num, eachByteSize);
}

void deletePP(void** &pp, const int num)
{
	return peace::base::deletePP(pp, num);
}

/**************************************************/ 



/************************ net *********************/ 
void* netCreate(const char *type, void *arg, const bool useMmsg)
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

	peace::net::NetBase *s = peace::net::NetBase::create(t, arg, useMmsg);
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

void* udpServerCreate(void* arg)
{
	return netCreate("udpServer", arg);
}

void* udpClientCreate(void* arg)
{
	return netCreate("udpClient", arg);
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


/********************* media ***********************/
void mediaReadSplitH264(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize)
{
    peace::media::ReadSplitBase *r = peace::media::ReadSplitBase::create("h264");
    if(!r)
    {
        LOGD("new ReadSplitH264 fail !\n");
        return;
    }

    r->deal(fileAbsName, dealFunc, arg, readBuf, readBufSize);
}

void mediaReadSplitAAC(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize)
{
    peace::media::ReadSplitBase *r = peace::media::ReadSplitBase::create("aac");
    if(!r)
    {
        LOGD("new ReadSplitAAC fail !\n");
        return;
    }

    r->deal(fileAbsName, dealFunc, arg, readBuf, readBufSize);
}

/***************************************************/


/********************* other ***********************/
void* mmsgRecvInit(const char *ip, const int port)
{
	peace::other::MmsgRecv *r = new peace::other::MmsgRecv();
	if(!r)
	{
		LOGD("new %s fail !\n", __FUNCTION__);
		return NULL;
	}

	int ret = r->init(ip, port);
	if(ret < 0)
	{
		LOGD("r->init fail ! %d\n", ret);
		return NULL;
	} 

	return (void*)r;
}

int mmsgRecvDo(void* recv)
{
	peace::other::MmsgRecv *r = (peace::other::MmsgRecv*)recv;
	if(!r)
	{
		LOGD("%s: para NULL !\n", __FUNCTION__);
		return -1;
	} 

	return r->recv();
}

void mmsgRecvExit(void *recv)
{
	peace::other::MmsgRecv *r = (peace::other::MmsgRecv*)recv;
	if(!r)
	{
		LOGD("%s: para NULL !\n", __FUNCTION__);
		return;
	} 

	r->exit();
	delete r;	
}

/***************************************************/



