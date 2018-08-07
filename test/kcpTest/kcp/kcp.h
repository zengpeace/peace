#ifndef _KCP_H_
#define _KCP_H_ 

#include "peaceInterface.h"
#include "ikcp.h"


class Kcp 
{
public:
	typedef int(*KcpOutFuncType)(const char *buf, int len, ikcpcb *kcp, void *user);

public:
	int init(const int conv, void* user, const int kcpMode, const KcpOutFuncType udpSendFunc, const KcpOutFuncType kcpRecvFunc);	
	void exit();

	int recvUdpPackage(const unsigned char *data, const int dataSize);
	int sendPackage(const unsigned char *data, const int dataSize);	

public:
	static void send(const unsigned char *data, const int dataSize, void* arg);
	void _send(const unsigned char *data, const int dataSize);
	static void* recvThread(void *arg);
	void _recvThread();
	static void* updateThread(void* arg);	
	void _updateThread();

private:
	bool _isRunning;
	pthread_t _updateTid;
	pthread_t _recvTid;
	ikcpcb *_kcp;
	pthread_mutex_t _sendLock;
	pthread_mutex_t _recvLock;
	
	void* _user;
	KcpOutFuncType _recvFunc;

#define DEFAULT_SIZE 2 * 1024 * 1024
	char _buf[DEFAULT_SIZE];
	static const int _bufSize = DEFAULT_SIZE;
};


#endif

