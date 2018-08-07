#include "kcp.h"

int Kcp::init(const int conv, void* user, const int kcpMode, const KcpOutFuncType udpSendFunc, const KcpOutFuncType kcpRecvFunc)
{
	int ret;
	ret = pthread_mutex_init(&_sendLock, NULL);
	if(ret < 0)
	{
		LOGD("mutex init fail ! _sendLock\n");
		return -1;
	}
	else 
	{
		LOGD("mutex init success ! _sendLock\n");
	}

	ret = pthread_mutex_init(&_recvLock, NULL);
	if(ret < 0)
	{
		LOGD("mutex init fail ! _recvLock\n");
		return -2;
	}
	else 
	{
		LOGD("mutex init success ! _recvLock\n");
	}

	_kcp = ikcp_create(conv, user);
	_kcp->output = udpSendFunc;
	ikcp_wndsize(_kcp, 1024, 1024);
	if (kcpMode == 0) 
	{
		ikcp_nodelay(_kcp, 0, 10, 0, 0);
	}
	else if (kcpMode == 1) 
	{
		ikcp_nodelay(_kcp, 0, 10, 0, 1);
	}	
	else 
	{
		ikcp_nodelay(_kcp, 1, 10, 2, 1);
		_kcp->rx_minrto = 10;
		_kcp->fastresend = 1;
	}

	_user = user;	
	_recvFunc = kcpRecvFunc;
	_isRunning = true;
	threadCreateMiddle(_updateTid, this->updateThread, (void*)this);
	threadCreateMiddle(_recvTid, this->recvThread, (void*)this);	

	//LOGD("mss is %d\n", _kcp->mss);
	
	return 0;
}

void Kcp::exit()
{
	LOGD("into %s\n", __FUNCTION__);
	_isRunning = false;
	threadClose(_updateTid);
	threadClose(_recvTid);
	ikcp_release(_kcp);
	_kcp = NULL;

	pthread_mutex_destroy(&_sendLock);
	pthread_mutex_destroy(&_recvLock);
}


int Kcp::recvUdpPackage(const unsigned char *data, const int dataSize)
{
	LOGD("kcp recv %d data !\n", dataSize);
	pthread_mutex_lock(&_recvLock);
	ikcp_input(_kcp, (const char*)data, (long)dataSize);
	pthread_mutex_unlock(&_recvLock);
	return 0;
}

void* Kcp::recvThread(void *arg)
{
	Kcp *c = (Kcp*)arg;
	c->_recvThread();
	return NULL;
}

void Kcp::_recvThread()
{
	int packageSize;
	//int nextPackageNum = 0;
	//int sn;
	while(_isRunning)
	{
		pthread_mutex_lock(&_recvLock);
		packageSize = ikcp_recv(_kcp, _buf, _bufSize);
		pthread_mutex_unlock(&_recvLock);
		if(packageSize <= 0)
		{
			//LOGD("not recv data ! %d\n", packageSize);
			continue;
		}
		
		/*sn = *(int*)(_buf + 0);
		if(sn != nextPackageNum)
		{
			LOGD("error sn ! sn=%d, next=%d\n", sn, nextPackageNum);
		}
		else 
		{
			LOGD("sn right ! %d\n", sn);
		}
		nextPackageNum ++;*/
		_recvFunc(_buf, packageSize, _kcp, _user);

		usleep(25 * 1000);
	}
}

void Kcp::send(const unsigned char *data, const int dataSize, void* arg)
{
	Kcp *k = (Kcp*)arg;
	k->_send(data, dataSize);
}

void Kcp::_send(const unsigned char *data, const int dataSize)
{
	this->sendPackage(data, dataSize);
	usleep(30 * 1000);
}

int Kcp::sendPackage(const unsigned char *data, const int dataSize)
{
	//LOGD("_kcp is %p\n", _kcp);
	//LOGD("2 mss is %d\n", _kcp->mss);
	//LOGD("2 _kcp is %p\n", _kcp);

	//LOGD("send package dataSize is %d\n", dataSize);	
	pthread_mutex_lock(&_sendLock);
	ikcp_send(_kcp, (const char *)data, dataSize);
	pthread_mutex_unlock(&_sendLock);
	return 0;
}

void* Kcp::updateThread(void* arg)
{
	Kcp *k = (Kcp*)arg;
	k->_updateThread();
	return NULL;
}

void Kcp::_updateThread()
{
	while(_isRunning)
	{
		usleep(20 * 1000);
		ikcp_update(_kcp, getCurMs());	
	}
}





