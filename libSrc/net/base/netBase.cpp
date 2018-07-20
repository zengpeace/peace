#include "net/base/netBase.h"
#include "net/tcp/tcpServer.h"
#include "net/tcp/tcpClient.h"
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
	_alreadyStart = false;
	_useSendThread = false;
}

NetBase::~NetBase()
{

}

NetBase* NetBase::create(const NetType type, void* arg)
{
	UdpServer *us = NULL;
	UdpClient *uc = NULL;
	//TcpServer *ts = NULL;
	//Tcpclient *tc = NULL;
	NetBase *b = NULL;
	switch(type)
	{
		case eNetUdpServer:
			us = new UdpServer();
			if(us)
			{
				b = static_cast<NetBase*>(us);
			}
			break;

		case eNetUdpClient:
			uc = new UdpClient();
			if(uc)
			{
				b = static_cast<NetBase*>(uc);
			}
			break;

		/*case eNetTcpServer:
			ts = new TcpServer();
			if(!ts)
			{
				b = static_cast<NetBase*>(ts);
			} 
			break;

		case eNetTcpClient:
			tc = new TcpClient();
			if(tc)
			{
				b = static_cast<NetBase*>(tc);
			}	
			break;*/

		default:
			LOGD("unknow net type %u\n", (unsigned int)type);
			break;
	}
	
	if(b)
	{
		b->_myNetType = type;
		b->_businessDealFuncArg = arg;
	}

	return b;
}


void NetBase::setChainSize(const int chainSize)
{
	if(!_alreadyStart)
	{
    	_chainSize = chainSize;
	}
	else 
	{
		LOGD("can not set chain size after start !\n");
	}
}

void NetBase::setUseSendThread()
{
	if(!_alreadyStart)
	{
    	_useSendThread = true;
	}
	else 
	{
		LOGD("can not set use send thread after start !\n");
	}
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

