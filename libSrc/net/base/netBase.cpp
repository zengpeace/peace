#include "net/base/netBase.h"
//#include "net/tcp/tcpServer.h"
//#include "net/tcp/tcpClient.h"
#include "net/udp/udpServer.h"
#include "net/udp/udpClient.h"


namespace peace 
{
namespace net 
{

NetBase::NetBase()
{
	_myNetType = eNetTcpServer;
	_chainSize = CHAIN_SIZE;
}

NetBase::~NetBase()
{

}

NetBase* NetBase::create(const NetType type)
{
	UdpServer *us = NULL;
	UdpClient *uc = NULL;
	NetBase *b = NULL;
	switch(type)
	{
		case eNetUdpServer:
			us = new UdpServer();
			if(!us)
			{
				return NULL;
			}
			b = static_cast<NetBase*>(us);
			break;

		case eNetUdpClient:
			uc = new UdpClient();
			if(!uc)
			{
				return NULL;
			}
			b = static_cast<NetBase*>(uc);
			break;

		case eNetTcpServer:
			break;

		case eNetTcpClient:
			break;

		default:
			LOGD("unknow net type %u\n", (unsigned int)type);
			break;
	}
	
	if(b)
	{
		b->_myNetType = type;
	}

	return b;
}


void NetBase::setChainSize(const int chainSize)
{
    _chainSize = chainSize;
}

void NetBase::registerTcpBusinessDealFunc(const TcpBusinessDealFuncType pFunc)
{
	if(_myNetType != eNetTcpServer && _myNetType != eNetTcpClient)
	{
		LOGD("%s: type error ! _myType is %u\n", __FUNCTION__, (unsigned int)_myNetType);
		return;
	}

	_tcpBusinessDealFunc = pFunc;
}

void NetBase::registerUdpBusinessDealFunc(const UdpBusinessDealFuncType pFunc)
{
	if(_myNetType != eNetUdpServer && _myNetType != eNetUdpClient)
	{
		LOGD("%s: type error ! _myType is %u\n", __FUNCTION__, (unsigned int)_myNetType);
		return;
	}
		
	_udpBusinessDealFunc = pFunc;
}

} //namespace net 
} //namespace peace

