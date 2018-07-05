#include "net/udp/udpServer.h"

namespace peace 
{
namespace net 
{

UdpServer::UdpServer()
{

}

UdpServer::~UdpServer()
{
	
}

int UdpServer::selfBind(const char *ip, const int nPort, const int sendBufSize, const int recvBufSize)
{
	int sock = bindSocket(eUdpServer, ip, nPort, sendBufSize, recvBufSize);
	if(sock <= 0)
	{
		LOGD("%s: fail ! ip=%s, nPort=%d, ret=%d\n", __FUNCTION__, ip, nPort, sock);
		return -1;
	}

	savePeerAddr(ip, nPort);
	return sock;
}

} //namespace net 
} //namespace peace 



