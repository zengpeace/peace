#include "base.h"
#include "client.h"
#include "server.h"


Base* Base::create(const char *id)
{
	Client *c = NULL;
	Server *s = NULL;
	Base *b = NULL;
	std::string ID = id;
	if(ID == "server")
	{
		s = new Server();
		if(!s)
		{
			return NULL;
		}
		b = static_cast<Base*>(s);
	}
	else if(ID == "client")
	{
		c = new Client();
		if(!c)
		{
			return NULL;
		}
		b = static_cast<Base*>(c);
	}

	if(b)
	{
		b->_id = id;
		b->_bufSize = _I_BUF_SIZE;	
		memset(&b->_tmpPeerAddr, 0, sizeof(sockaddr_in));	
	}

	return b;
}


Base* Base::create(const char *ip, const int port, const int kcpMode, const char *id, void* initExLogicArgs)
{
	Base *base = Base::create(id);
	if(!base)
	{
		return NULL;
	}

	int ret;
	ret = base->init(ip, port, kcpMode, id, initExLogicArgs);
	if(ret < 0)
	{
		LOGD("base ubut fail ! ret = %d\n", ret);
		return NULL;
	}

	return base;
}

Base::~Base()
{
	LOGD("call %s\n", __FUNCTION__);
}

int Base::init(const char *ip, const int port, const int kcpMode, const char *udpId, void* initExLogicArgs)
{
	LOGD("+++%s\n", __FUNCTION__);
	int ret;
	ret = _kcp.init(0x11223344, (void*)this, 0, this->kcpOutputFunc, this->kcpRecvFunc);
	if(ret < 0)
	{
		LOGD("kcp init fail ! ret = %d\n", ret);
		return -1;
	}

	std::string id = udpId;
	std::string useid;
	if(id == "client")
	{
		useid = "udpClient";
	}
	else if(id == "server")
	{
		useid = "udpServer";
	}
	else 
	{
		LOGD("udpId error ! %s\n", udpId);
		return -2;
	}

	_udp = netCreate(useid.c_str(), (void*)this);
	netRegisterUdpBusFunc(_udp, this->recvUdpPackage);
	netStart(_udp, ip, port);

	ret = initExLogic(initExLogicArgs);
	if(ret < 0)
	{
		LOGD("initExLogic fail ! ret = %d\n", ret);
		_kcp.exit();
		return -3;
	}
	
	return 0;
}

void Base::exit()
{
	netStop(_udp);
	netDestroy(_udp);
	_udp = NULL;	

	_kcp.exit();
	exitExLogic();
}

int Base::kcpOutputFunc(const char *buf, int len, ikcpcb *kcp, void *user)
{
	//LOGD("into %s ! len=%d, conv=%x\n", __FUNCTION__, len, kcp->conv);
	Base *b = (Base*)user;
	if(b->_id == "server" && b->_tmpPeerAddr.sin_port > 0)
	{
		return netSend(b->_udp, (const unsigned char*)buf, len, b->_tmpPeerAddr);
	}
	else if(b->_id == "client")
	{
		return netSend(b->_udp, (const unsigned char*)buf, len);
	}
	else 
	{
		return -1;
	}
}

int Base::recvUdpPackage(void *udp, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr, void* arg)
{
	Base *b = (Base*)arg;
	b->_tmpPeerAddr = peerAddr;
	return b->_kcp.recvUdpPackage(data, dataSize);
}

int Base::kcpRecvFunc(const char *buf, int len, ikcpcb *kcp, void* user)
{
	Base *base = (Base*)user;
	return base->_kcpRecvFunc(buf, len, kcp);
}


