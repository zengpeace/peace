#ifndef _BASE_H_
#define _BASE_H_ 

#include "../kcp/kcp.h"

class Base
{
public:
	static Base* create(const char *id);
	static Base* create(const char *ip, const int port, const int kcpMode, const char *id, void* initExLogicArgs);
	virtual ~Base();

public:
	int init(const char *ip, const int port, const int kcpMode, const char *udpId, void* initExLogicArgs = NULL);	
	void exit();

public:
	virtual int initExLogic(void* arg) = 0;
	virtual void exitExLogic() = 0;

	virtual int _kcpRecvFunc(const char *buf, const int len, ikcpcb *kcp) = 0;
	static int kcpRecvFunc(const char *buf, int len, ikcpcb *kcp, void* user);

	static int recvUdpPackage(void *udp, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr, void* arg);
	int _recvUdpPackage(void *udp, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr);
	static int kcpOutputFunc(const char *buf, int len, ikcpcb *kcp, void *user);

public:
	std::string _id;
#define _I_BUF_SIZE 2 * 1024 * 1024
	unsigned char _buf[_I_BUF_SIZE];
	int _bufSize;
	struct sockaddr_in _tmpPeerAddr;


protected:
	Kcp _kcp;
	void *_udp;
};


#endif

