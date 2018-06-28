#ifndef _PEACE_NET_UDP_UDP_SERVER_H_
#define _PEACE_NET_UDP_UDP_SERVER_H_ 

#include "net/udp/udp.h"

namespace peace 
{
namespace net 
{

class UdpServer : public Udp   
{
public:
	UdpServer();
	~UdpServer();	
	virtual int start(const char *ip, const int port);	
	virtual void stop();	

private:
	int _lockSemNotFinishInit;
	pthread_mutex_t _LockChain;
	pthread_mutex_t _LockSend;
	pthread_mutex_t _LockData;
	int _sock;
	RecvData *_recvDataUdp;
	RecvData *_recvDataBuf;
	RecvData *_recvDataBufLast;
	sem_t  _taskSem;
};


} //namespace net 
} //namespace peace 


#endif

