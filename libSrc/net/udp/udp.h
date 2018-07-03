#ifndef _PEACE_NET_UDP_UDP_H_
#define _PEACE_NET_UDP_UDP_H_ 


#include "net/base/netBase.h"

namespace peace 
{
namespace net 
{

class Udp : public NetBase  
{
public:
	Udp();
	~Udp();	

	virtual int init();
	virtual void exit();
	virtual int start(const char *ip, const int port, const int sockSendBufSize, const int sockRecvBufSize);	
	virtual void stop();
	
	virtual int send(const char *data, const int dataSize, const struct sockaddr_in &peerAddr);	
	virtual int send(const char *data, const int dataSize, const int sock);
	virtual int send(const char *data, const int dataSize);
	
	static int bindSocket(const UdpUserType type, const char *ip, const int nPort, const int sendBufSize, const int recvBufSize);
	virtual int selfBind(const char *ip, const int nPort, const int sendBufSize, const int recvBufSize) = 0;

	static void* bufServer(void* arg);
    static void* recvServer(void* arg);
    void _bufServer();
    void _recvServer();

	void savePeerAddr(const char *ip, const int port);

private:
	bool _lockSemFinishInit;
	pthread_mutex_t _LockChain;
	pthread_mutex_t _LockSend;
	pthread_mutex_t _LockData;
	int _sock;
	RecvData *_recvDataUdp;
	RecvData *_recvDataBuf;
	RecvData *_recvDataBufLast;
	sem_t _taskSem;

	pthread_mutex_t _LockSend;

	bool _isRunning;	
	pthread_t _bufServerPid;
	pthread_t _recvServerPid;

	int _myPort;
	struct sockaddr_in _orgPeerAddr;
};

} //namespace net 
} //namespace peace 


#endif

