#include "net/base/netBase.h"
#include "net/tcp/tcp.h"
#include "net/udp/udp.h"
//#include "net/tcp/tcpServer.h"
//#include "net/tcp/tcpClient.h"
#include "net/udp/udpServer.h"
//#include "net/udp/udpClient.h"


namespace peace 
{
namespace net 
{

//class Udp;
//class UdpServer;

NetBase::NetBase()
{
	_businessDealFunc = NULL;


}

NetBase::~NetBase()
{
	_businessDealFunc = NULL;

}

NetBase* NetBase::create(const NetType type)
{
	UdpServer *us = NULL;
	switch(type)
	{
		case eNetUdpServer:
			us = new UdpServer();
			if(!us)
			{
				return NULL;
			}

			return static_cast<NetBase*>(us);
			break;
		case eNetUdpClient:
			return NULL;
			break;
		case eNetTcpServer:
			return NULL;
			break;
		case eNetTcpClient:
			return NULL;
			break;
		default:
			LOGD("unknow net type %u\n", (unsigned int)type);
			return NULL;
			break;
	}
}

void NetBase::registerBusinessDealFunc(const NetBusinessDealFuncType pFunc)
{
	_businessDealFunc = pFunc;
}


} //namespace net 
} //namespace peace

