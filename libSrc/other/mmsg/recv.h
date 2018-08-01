#ifndef _PEACE_OTHER_MMSG_RECV_H_
#define _PEACE_OTHER_MMSG_RECV_H_ 

#include "types.h"

namespace peace 
{
namespace other 
{

class MmsgRecv 
{
#define MMSG_RECV_HDR_NUM 	2
#define MMSG_RECV_IOV_SIZE 	3 
#define MMSG_RECV_BUF_SIZE 	32

private:
	static const int _timeout = 10;

public:
	int init(const char *ip, const int port);	
	int recv();
	void exit();

private:
	void initMmsgPara();
	
	int _sock;
	struct sockaddr_in _peerAddr;
	
	struct mmsghdr _msgs[MMSG_RECV_HDR_NUM];
	struct iovec _msgsIovec[MMSG_RECV_HDR_NUM][MMSG_RECV_IOV_SIZE];
	unsigned char _buf[MMSG_RECV_HDR_NUM][MMSG_RECV_IOV_SIZE][MMSG_RECV_BUF_SIZE];
	struct sockaddr_in _addr[MMSG_RECV_HDR_NUM];	
};

}
}
#endif

