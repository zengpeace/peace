#include "net/udp/udpClient.h"


namespace peace 
{
namespace net 
{

int UdpClient::selfBind(const char *ip, const int nPort, const int sendBufSize, const int recvBufSize)
{
	int sock = -1;
	for(int port = gUdpClientSelfPortRangeBegin; port < gUdpClientSelfPortRangeEnd; port ++)
	{
		sock = bindSocket(eUdpClient, "0.0.0.0", port, sendBufSize, recvBufSize);
		if(sock > 0)
		{
			savePeerAddr(ip, port);
			return sock;
		}
	}

	return -1;
}

} //namespace net 
} //namespace peace 

