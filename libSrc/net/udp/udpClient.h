#ifndef _PEACE_NET_UDP_UDP_CLIENT_H_
#define _PEACE_NET_UDP_UDP_CLIENT_H_ 


#include "net/udp/udp.h"


namespace peace 
{
namespace net 
{

class UdpClient : public Udp 
{
public:
	virtual int selfBind(const char *ip, const int nPort, const int sendBufSize, const int recvBufSize);
	

};


} //namespace net 
} //namespace peace 

#endif


