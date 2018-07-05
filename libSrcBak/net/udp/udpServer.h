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

	virtual int selfBind(const char *ip, const int nPort, const int sendBufSize, const int recvBufSize) override;

private:

};


} //namespace net 
} //namespace peace 


#endif

