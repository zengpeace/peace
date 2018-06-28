#ifndef _PEACE_NET_UDP_UDP_SERVER_H_
#define _PEACE_NET_UDP_UDP_SERVER_H_ 

#include "net/udp/udpServer.h"


namespace peace 
{
namespace net 
{

UdpServer::UdpServer()
{
	_lockSemNotFinishInit = -1;
	_sock = -1;
	_recvDataUdp = NULL;
	_recvDataBuf = NULL;
	_recvDataBufLast = NULL;
}

UdpServer::~UdpServer()
{

}

int UdpServer::start(const char *ip, const int port)
{
	if(_businessDealFunc == NULL)
	{
		LOGD("businessDealFunc do not register correct !\n");
		return -1;
	}

	return 0;		
}

void UdpServer::stop()
{

}

} //namespace net 
} //namespace peace 


#endif

