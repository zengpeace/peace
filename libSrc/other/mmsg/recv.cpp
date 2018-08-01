#include "recv.h"

namespace peace
{
namespace other
{

int MmsgRecv::init(const char *ip, const int port)
{
	_sock = socket(AF_INET, SOCK_DGRAM, 0);
	_peerAddr.sin_family = AF_INET;
	_peerAddr.sin_addr.s_addr = inet_addr(ip);
	_peerAddr.sin_port = htons((const short)port);
	bind(_sock, (struct sockaddr*)&_peerAddr, sizeof(struct sockaddr_in));	
	
	return 0;
}

void MmsgRecv::initMmsgPara()
{
	memset(_msgs, 0, sizeof(_msgs));
	struct msghdr *hdr;
	struct iovec *io;
	for(int i = 0; i < MMSG_RECV_HDR_NUM; i ++)
	{
		io = &_msgsIovec[i];
		io->iov_base = _buf[i];
		io->iov_len = MMSG_RECV_BUF_SIZE;
		
		hdr = &_msgs[i].msg_hdr;
		hdr->msg_iov = io;
		hdr->msg_iovlen = 1;
	}
}

int MmsgRecv::recv()
{
	initMmsgPara();
	struct timespec timeout = {_timeout, 0};
	int ret = recvmmsg(_sock, _msgs, MMSG_RECV_HDR_NUM, 0, &timeout);
	LOGD("recvmmsg return %d\n", ret);
	for(int i = 0; i < ret; i ++)
	{
		_buf[i][_msgs[i].msg_len] = 0;
		LOGD("%d: %s\n", i, _buf[i]);
	}

	return ret;
}

void MmsgRecv::exit()
{

}

} //namespace other 
} //namespace peace 

