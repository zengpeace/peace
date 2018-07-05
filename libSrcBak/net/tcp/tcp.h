#ifndef _PEACE_NET_TCP_TCP_H_
#define _PEACE_NET_TCP_TCP_H_ 

#include "net/base/netBase.h"

namespace peace 
{
namespace net 
{
class Tcp : public NetBase
{
public:
	virtual int init();
	virtual void exit();
	virtual int start(const char *ip, const int port, const int sockSendBufSize, const int sockRecvBufSize);
	virtual void stop();         

	virtual int send(const unsigned char *data, const int dataSize, const int sock);
	virtual int send(const unsigned char *data, const int dataSize);

private:


};

} //namespace net 
} //namespace peace 





#endif

