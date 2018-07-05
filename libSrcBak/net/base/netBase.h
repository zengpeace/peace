#ifndef _PEACE_NET_BASE_NET_BASE_H_ 
#define _PEACE_NET_BASE_NET_BASE_H_ 

#include "types.h"
#include "base/base.h"


namespace peace 
{
namespace net 
{

class NetBase
{
public:     
	typedef enum 
	{
		eNetTcpServer,
		eNetTcpClient,
		eNetUdpServer,
		eNetUdpClient,
	}NetType;

	NetBase();
	virtual ~NetBase();

	static NetBase* create(const NetType type);	
	void setChainSize(const int chainSize);	
	void setUseSendThread();

	virtual int init() = 0;
	virtual void exit() = 0;
	virtual int start(const char *ip, const int port, const int sockSendBufSize, const int sockRecvBufSize) = 0;
	virtual void stop() = 0;	 

	virtual int send(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr) = 0;
	virtual int send(const unsigned char *data, const int dataSize, const int sock) = 0;
	virtual int send(const unsigned char *data, const int dataSize) = 0;

	void registerTcpBusinessDealFunc(const TcpBusinessDealFuncType pFunc);
	void registerUdpBusinessDealFunc(const UdpBusinessDealFuncType pFunc);	

public:
	bool _alreadyStart;
	int _chainSize;
	bool _useSendThread;
	BlockInfo _sendBlock;
	TcpBusinessDealFuncType _tcpBusinessDealFunc;
	UdpBusinessDealFuncType _udpBusinessDealFunc;
	NetType _myNetType;
};


} //namespace net 
} //namespace peace 


#endif

