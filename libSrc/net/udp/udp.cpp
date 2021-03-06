#include "net/udp/udp.h"


namespace peace 
{
namespace net 
{

Udp::Udp()
{
	_lockSemFinishInit = false;
	_sock = -1;
	_recvDataUdp = NULL;
	_recvDataBuf = NULL;
	_recvDataBufLast = NULL;

	_isRunning = false;
	_bufServerPid = -1;
	_recvServerPid = -1;
	_sendServerTid = -1;

	_mmsgRecvNum = UDP_REV_MMSG_NUM;
	memset(_msgVec, 0, sizeof(_msgVec));
	
	void** tmpRecvBuf = base::newPP(_mmsgRecvNum);
	_mmsgRecvBuf = (RecvData**)tmpRecvBuf;	

	_mmsgSendNum = UDP_SND_MMSG_NUM;
}

Udp::~Udp()
{

}

void Udp::initMmsgPara()
{
	struct msghdr *one;
	for(int i = 0; i < _mmsgRecvNum; i ++)
	{
		one = &_msgVec[i].msg_hdr;
		_mmsg_msg_iov[i].iov_base = _mmsgRecvBuf[i]->buf;
		_mmsg_msg_iov[i].iov_len = UDP_BUF_SIZE;
		
		one->msg_name = &(_mmsgRecvBuf[i]->addr);
		one->msg_namelen = sizeof(struct sockaddr_in);
		one->msg_iov = &_mmsg_msg_iov[i];
		one->msg_iovlen = UDP_REV_MMSG_IOV_NUM;
	}
}

void Udp::initMmsgSendPara(const unsigned char* data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	struct msghdr *one;
	for(int i = 0; i < _mmsgSendNum; i ++)
	{
		one = &_mmsgSendVec[i].msg_hdr;
		_mmsgSendIov[i].iov_base = _mmsgSendIovBase[i];
		_mmsgSendIov[i].iov_len = UDP_BUF_SIZE;
		one->msg_name = &_mmsgSendName[i];	
		one->msg_namelen = sizeof(struct sockaddr_in);
		one->msg_iov = &_mmsgSendIov[i];
		one->msg_iovlen = 1;

		memcpy(&_mmsgSendName[i], &peerAddr, sizeof(struct sockaddr_in));
		memcpy(&_mmsgSendIovBase[i], data, dataSize);
	}
}


int Udp::init()
{
	//_chainSize = 50;
	_recvDataUdp = base::CreateChain(_chainSize);
	if(!_recvDataUdp) 
	{
		LOGD("CreateChain fail !\n");
		return -2;
	}	

	LOGD("%s: %p,%p, %p\n", __FUNCTION__, _recvDataUdp, _mmsgRecvBuf[0], _mmsgRecvBuf);

	if (!_lockSemFinishInit)
	{
		if (pthread_mutex_init(&_LockChain, NULL))
		{
			LOGD("pthread_mutex_init failure !\n");
		}
		else if(pthread_mutex_init(&_LockSend, NULL))
		{
			LOGD("pthread_mutex_init failure !\n");
			pthread_mutex_destroy(&_LockChain);
		}
		else if (pthread_mutex_init(&_LockData, NULL))
		{
			LOGD("pthread_mutex_init failure !\n");
			pthread_mutex_destroy(&_LockChain);
			pthread_mutex_destroy(&_LockSend);
		}
		else if (sem_init(&_taskSem, 0, 0))
		{
			LOGD("sem_init failure !\n");
			pthread_mutex_destroy(&_LockChain);
			pthread_mutex_destroy(&_LockSend);
			pthread_mutex_destroy(&_LockData);
			sem_destroy(&_taskSem);
		}
		else
		{
			_lockSemFinishInit = true;
		}

		if (!_lockSemFinishInit)
		{
			return -3;
		}
	}

	return 0;
}

int Udp::start(const char *ip, const int port, const int sockSendBufSize, const int sockRecvBufSize)
{
	LOGD("into %s: ip=%s, port=%d\n", __FUNCTION__, ip, (int)port);
	int ret;
	if(_udpBusinessDealFunc == NULL)
	{
		LOGD("businessDealFunc do not register correct !\n");
		return -1;
	}

	_myPort = port;
	_sock = selfBind(ip, port, sockSendBufSize, sockRecvBufSize);		
	if(_sock <= 0)
	{
		LOGD("selfBind fail ! _sock = %d\n", _sock);
		return -2;
	}

	LOGD("id is %u, _myport is %d, peerPort is %d\n", (unsigned int)_myNetType, _myPort, (int)ntohs(_orgPeerAddr.sin_port));
	_isRunning = true;
	if(_useSendThread)
	{
		ret = base::queueInit(&_sendBlock, 1024, gNetSendQueueBufSize);
		if(ret < 0)
		{
			LOGD("%s: queue init fail !\n", __FUNCTION__);
			_isRunning = false;
			return -3;
		}

		ret = base::threadCreateMiddle(_sendServerTid, sendServer, (void*)this);
		if(ret < 0)
		{
			LOGD("threadCreateMiddle fail ! sendServer %d\n", ret);
			base::queueDestroy(&_sendBlock);
			_isRunning = false;
			return -4;
		}
	}	

	ret = base::threadCreateMiddle(_bufServerPid, bufServer, (void*)this);
	if(ret < 0)
	{
		LOGD("threadCreateMiddle fail ! bufServer %d\n", ret);
		_isRunning = false;
		if(_useSendThread)
		{
			base::threadClose(_sendServerTid);	
			base::queueDestroy(&_sendBlock);
		}

		base::threadClose(_sendServerTid);
		return -5;
	}

	ret = base::threadCreateMiddle(_recvServerPid, recvServer, (void*)this);
    if(ret < 0)
    {
        LOGD("threadCreateMiddle fail ! recvServer %d\n", ret);
		_isRunning = false;
		if(_useSendThread)
		{
			base::threadClose(_sendServerTid);	
			base::queueDestroy(&_sendBlock);
		}
		base::threadClose(_bufServerPid);
        return -6;
    }

	return 0;		
}

void Udp::stop()
{
	_isRunning = false;
	base::threadClose(_recvServerPid);
	base::threadClose(_bufServerPid);	
}

void Udp::exit()
{
	sem_destroy(&_taskSem);	
	pthread_mutex_destroy(&_LockData);
	pthread_mutex_destroy(&_LockSend);
	pthread_mutex_destroy(&_LockChain);

	_lockSemFinishInit = false;
	base::ReleaseChain(&_recvDataUdp);
}

void* Udp::sendServer(void* arg)
{
	Udp *u = (Udp*)arg;
	u->_sendServer();
	return NULL;
}

void Udp::_sendServer()
{
	base::queuePop(&_sendBlock, Udp::sendServerDealFunc, (void*)this, Udp::isStart, (void*)this, 2);
}

void Udp::sendServerDealFunc(const unsigned char* data, const int dataSize, void* arg)
{
	Udp *u = (Udp*)arg;
	u->_sendServerDealFunc(data, dataSize);
}

void Udp::_sendServerDealFunc(const unsigned char *data, const int dataSize)
{
	const struct sockaddr_in *peerAddr = (const struct sockaddr_in*)data;
	size_t headBytes = sizeof(struct sockaddr_in);
	const unsigned char *realData = &data[headBytes];
	int realDataSize = dataSize - headBytes;

	if(_useMmsg)
	{
		realSendEx(realData, realDataSize, *peerAddr);
	}
	else 
	{	
		realSend(realData, realDataSize, *peerAddr);
	}
}

bool Udp::isStart(void *arg)
{
	Udp *u = (Udp*)arg;
	return u->_isRunning;
}

void* Udp::bufServer(void* arg)
{
	Udp* u = (Udp*)arg;
	u->_bufServer();
	return NULL;
}

void Udp::_bufServer()
{
	RecvData *recvDataTmp = NULL;
	RecvData *recvDataBak = NULL;
	struct timespec ts;
	struct timeval  tv;

	while (_isRunning)
	{
		gettimeofday(&tv, NULL);

		ts.tv_sec = tv.tv_sec + 2;
		ts.tv_nsec = tv.tv_usec * 1000;

		if (sem_timedwait(&(_taskSem), &ts) != 0)	continue;

		//LOGD("%s: recv _taskSem\n", __FUNCTION__);

		pthread_mutex_lock(&(_LockData));
		recvDataTmp = _recvDataBuf;
		_recvDataBuf = NULL;
		_recvDataBufLast = NULL;
		pthread_mutex_unlock(&(_LockData));

		//LOGD("%s: prepare to deal data ! %p\n", __FUNCTION__, recvDataTmp);
		while (recvDataTmp != NULL)
		{
			recvDataBak = recvDataTmp;
			recvDataTmp = recvDataTmp->pNext;
			recvDataBak->pNext = NULL;

			_udpBusinessDealFunc((void*)this, recvDataBak->buf, recvDataBak->count, recvDataBak->addr, _businessDealFuncArg);
			base::RecoveryChain(recvDataBak, &_recvDataUdp, &_LockChain);
		}
	}
}

void* Udp::recvServer(void *arg)
{
	Udp *u = (Udp*)arg;
	u->_recvServer();
	return NULL;
}

void Udp::_recvServer()
{
	int ret;
	Epollop epInfo;
	epInfo.epfd = epoll_create(EPOLL_MAX_EVENT);
	if (epInfo.epfd <= 0)
	{
		LOGD("epoll_create fail ! errno=%d, %s\n", errno, strerror(errno));
	}

	struct epoll_event *ev = &(epInfo.events[EPOLL_MAX_EVENT]);
	ev->events = EPOLLIN | EPOLLET;
	ev->data.fd = _sock;
	ret = epoll_ctl(epInfo.epfd, EPOLL_CTL_ADD, _sock, ev);
	if (ret < 0)
	{
		LOGD("epoll_ctl fail ! errno=%d, %s\n", errno, strerror(errno));
	}

	bool needBreak;
	int nfds, epfd = epInfo.epfd;
	int epollTimeout = 5;
	struct epoll_event *allEpev = epInfo.events;
	struct epoll_event *epev = &allEpev[0];
	while (_isRunning)
	{
		nfds = epoll_wait(epfd, allEpev, EPOLL_MAX_EVENT, epollTimeout);
		if (nfds < 0)
		{
			//LOGD("epoll_wait error ! errno=%d, %s\n", errno, strerror(errno));
			continue;
		}
		else if (nfds == 0) continue;
		else if (nfds > 1)
		{
			LOGD("epoll_wait nfds error ! nfds = %d\n", nfds);
			continue;
		}

		for (int i = 0; i < nfds; i ++)
		{
			epev = &(allEpev[i]);
			if((epev->events & EPOLLIN) && epev->data.fd == _sock)
			{
				needBreak = false;
				while(!needBreak)
				{
					if(_useMmsg)
					{
						needBreak = this->recvUdpLogicMul();
					}
					else 
					{
						needBreak = this->recvUdpLogic();
					}

					//LOGD("needBreak = %s\n", needBreak?"true":"false");
				}
			
				//LOGD("%d:prepare to sem post !\n", __LINE__);	
				sem_post(&(_taskSem));
			}
			else
			{
				LOGD("events,fd = %u,%d\n", epev->events, epev->data.fd);
			}
		}
	}
	if (_sock > 0)
	{
		close(_sock);
		_sock = -1;
	}
}

bool Udp::recvUdpLogic()
{
	socklen_t svrlen = sizeof(struct sockaddr_in);
	RecvData *recvDataTmp = NULL;
	pthread_mutex_lock(&(_LockChain));
	if (_recvDataUdp)
	{
		recvDataTmp = base::GetHeadChain(&_recvDataUdp);
	}
	pthread_mutex_unlock(&(_LockChain));

	if (recvDataTmp == NULL)
	{
		//LOGD("chain memory is not enough !{%s(%d)}\n", __FILE__, __LINE__);
		return true;
	}

	bool rret = false;
	recvDataTmp->pNext = NULL;
	recvDataTmp->count = recvfrom(_sock, recvDataTmp->buf, UDP_BUF_SIZE, 0, (struct sockaddr*)&(recvDataTmp->addr), &svrlen);
	if (recvDataTmp->count < 1)
	{
		//LOGD("count<1!count=%d,revents=%u,errno=%d,error:%s\n", recvDataTmp->count, (unsigned int)epev->events, errno, strerror(errno));
		//return;
		rret = true;

		base::RecoveryChain(recvDataTmp, &_recvDataUdp, &_LockChain);
	}
	else 
	{
		pthread_mutex_lock(&(_LockData));
		base::InsertTailEx(&_recvDataBuf, recvDataTmp, &_recvDataBufLast);
		pthread_mutex_unlock(&(_LockData));
	}

	recvDataTmp = NULL;
	return rret;
}

bool Udp::recvUdpLogicMul()
{
	int getnum = 0;
	pthread_mutex_lock(&(_LockChain));
	LOGD("%p, %d, %p\n", _recvDataUdp, _mmsgRecvNum, *_mmsgRecvBuf);
	getnum = base::GetHeadChain(&_recvDataUdp, _mmsgRecvNum, _mmsgRecvBuf);
	pthread_mutex_unlock(&(_LockChain));

	if (getnum != _mmsgRecvNum)
	{
		LOGD("chain memory is not enough ! %d {%s(%d)}\n", getnum, __FILE__, __LINE__);
		sleep(1);
		return true;
	}

	int n = 0;
	initMmsgPara();
	timespec tv = {1, 0};
	n = recvmmsg(_sock, _msgVec, _mmsgRecvNum, 0, &tv);
	LOGD("recvmmsg number is %d\n", n);
	for(int i = 0; i < n; i ++)
	{
		_mmsgRecvBuf[i]->count =  _msgVec[i].msg_len;
		LOGD("set count %d:%d\n", i, _mmsgRecvBuf[i]->count);
	}
	if(n < _mmsgRecvNum)
	{
		if(n < 0)
		{
			n = 0;
		}


		pthread_mutex_lock(&(_LockData));
		//LOGD("insertTailEx work list\n");
		base::InsertTailEx(&_recvDataBuf, _mmsgRecvBuf, &_recvDataBufLast, n);
		pthread_mutex_unlock(&(_LockData));

		pthread_mutex_lock(&_LockChain);
		for(int i = n; i < _mmsgRecvNum && _mmsgRecvBuf[i]; i ++)
		{
			//LOGD("insertHead recv list ! %d\n", i);
			base::InsertHead(&_recvDataUdp, _mmsgRecvBuf[i]);
			_mmsgRecvBuf[i] = NULL;
		}
		pthread_mutex_unlock(&_LockChain);
	}
	else 
	{
		//LOGD("insertTailEx work list");
		pthread_mutex_lock(&(_LockData));
		base::InsertTailEx(&_recvDataBuf, _mmsgRecvBuf, &_recvDataBufLast, _mmsgRecvNum);
		pthread_mutex_unlock(&(_LockData));
	}

	return true;
}

int Udp::realSendEx(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	initMmsgSendPara(data, dataSize, peerAddr);
	int ret;
	ret = sendmmsg(_sock, _mmsgSendVec, _mmsgSendNum, 0);
	LOGD("%s:sendmmsg return %d\n", __FUNCTION__, ret);
	return ret;
}

int Udp::realSend(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	static socklen_t svrlen = sizeof(struct sockaddr_in);
	int ret = sendto(_sock, data, dataSize, 0, (const struct sockaddr*)&peerAddr, svrlen);

	if (ret != dataSize)
	{
		char ipString[16];
		inet_ntop(AF_INET, (void*)&peerAddr, ipString, 16);
		LOGD("In MainSend: sendto failed! ret = %d, size = %d, %s:%d\n", ret, dataSize, ipString, ntohs(peerAddr.sin_port));
	}	

	return ret;
}

int Udp::send(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	//LOGD("peerAddr is %x:%d\n", ntohl(peerAddr.sin_addr.s_addr), (int)ntohs(peerAddr.sin_port));
	if(_useSendThread)
	{
		return base::queuePush(&_sendBlock, data, dataSize, (const unsigned char *)&peerAddr, sizeof(struct sockaddr_in));
	}

	int ret;
	pthread_mutex_unlock(&_LockSend);
	if(_useMmsg)
	{
		ret = realSendEx(data, dataSize, peerAddr);
	}
	else 
	{
		ret = realSend(data, dataSize, peerAddr);
	}
	pthread_mutex_lock(&_LockSend);
	return ret;
}

int Udp::send(const unsigned char *data, const int dataSize, const int sock)
{
	LOGD("api use error ! this api is used for tcp, not udp !\n");
	return -1;
}

int Udp::send(const unsigned char *data, const int dataSize)
{
	if(_myNetType != eNetUdpClient)
	{
		LOGD("only udp client can use this api ! your id is %u\n", (unsigned int)_myNetType);
		return -1;
	}

	return send(data, dataSize, _orgPeerAddr);
}

int Udp::bindSocket(const UdpUserType type, const char *ip, const int nPort, const int sendBufSize, const int recvBufSize)
{
	int iSocket;
	int flag = 1;
	int	len = sizeof(int);
	socklen_t svrlen;
	struct sockaddr_in localaddr;

	if ((iSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		return -1;
	}

	int optLen = sizeof(int);
	int rcvSize;

	getsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, (void *)&rcvSize, (socklen_t *)&optLen);
	LOGD("before:sock recv buf size = %u\n", rcvSize);
	getsockopt(iSocket, SOL_SOCKET, SO_SNDBUF, (void *)&rcvSize, (socklen_t *)&optLen);
	LOGD("before:sock send buf size = %u\n", rcvSize);

	if(type == eUdpServer)
	{
		setsockopt(iSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&flag, len);
	}

	rcvSize = sendBufSize / 2;
	setsockopt(iSocket, SOL_SOCKET, SO_SNDBUF, (const char *)&rcvSize, optLen);

	getsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, (void *)&rcvSize, (socklen_t *)&optLen);
	LOGD("mid:sock recv buf size = %u\n", rcvSize);
	getsockopt(iSocket, SOL_SOCKET, SO_SNDBUF, (void *)&rcvSize, (socklen_t *)&optLen);
	LOGD("mid:sock send buf size = %u\n", rcvSize);

	rcvSize = recvBufSize / 2;
	setsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, (const char *)&rcvSize, optLen);

	getsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, (void *)&rcvSize, (socklen_t *)&optLen);
	LOGD("after:sock recv buf size = %u\n", rcvSize);
	getsockopt(iSocket, SOL_SOCKET, SO_SNDBUF, (void *)&rcvSize, (socklen_t *)&optLen);
	LOGD("after:sock send buf size = %u\n", rcvSize);
		
	flag = fcntl(iSocket, F_GETFL, 0);
	flag |= O_NONBLOCK;
	if (fcntl(iSocket, F_SETFL, flag) == -1)
	{
		LOGD("set socket nonblock fail !\n");
		close(iSocket);
		return -2;
	}

	svrlen = sizeof(localaddr);
	memset((char *)&localaddr, 0x0, svrlen);

	unsigned short port = (unsigned short)nPort;

	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = inet_addr(ip);
	localaddr.sin_port = htons(port);

	if (bind(iSocket, (struct sockaddr *)&localaddr, svrlen) == -1)
	{
		close(iSocket);
		return -3;
	}

	return iSocket;
}

void Udp::savePeerAddr(const char *ip, const int port)
{
	//_myPort = port;
 	_orgPeerAddr.sin_family = AF_INET;
 	_orgPeerAddr.sin_port = htons(port);
 	_orgPeerAddr.sin_addr.s_addr = inet_addr(ip);
}

} //namespace net 
} //namespace peace 

