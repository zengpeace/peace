#ifndef _PEACE_NET_UDP_UDP_H_
#define _PEACE_NET_UDP_UDP_H_ 


#include "net/base/netBase.h"

namespace peace 
{
namespace net 
{

class Udp : public NetBase  
{
public:
#define UDP_REV_MMSG_NUM 4
#define UDP_REV_MMSG_IOV_NUM 1
#define UDP_SND_MMSG_NUM 1
#define UDP_SND_MMSG_IOV_NUM 3
	Udp();
	virtual ~Udp();	

	virtual int init() override;
	virtual void exit() override;
	virtual int start(const char *ip, const int port, const int sockSendBufSize, const int sockRecvBufSize) override;	
	virtual void stop() override;
	
	virtual int send(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr) override;	
	virtual int send(const unsigned char *data, const int dataSize, const int sock) override;
	virtual int send(const unsigned char *data, const int dataSize) override;

	static void* sendServer(void*arg);
	void _sendServer();
	static void sendServerDealFunc(const unsigned char* data, const int dataSize, void* arg);
	void _sendServerDealFunc(const unsigned char *data, const int dataSize);		
	static bool isStart(void* arg);

	static int bindSocket(const UdpUserType type, const char *ip, const int nPort, const int sendBufSize, const int recvBufSize);
	virtual int selfBind(const char *ip, const int nPort, const int sendBufSize, const int recvBufSize) = 0;

	static void* bufServer(void* arg);
    static void* recvServer(void* arg);
    void _bufServer();
    void _recvServer();

	void savePeerAddr(const char *ip, const int port);

private:
	int realSend(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr); 
	int realSendEx(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr); 
	bool recvUdpLogic();
	bool recvUdpLogicMul();
	void initMmsgPara();
	void initMmsgSendPara(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr);

public:
	bool _isRunning;

protected:
	int _myPort;
	struct sockaddr_in _orgPeerAddr;

private:
	bool _lockSemFinishInit;
	pthread_mutex_t _LockChain;
	pthread_mutex_t _LockSend;
	pthread_mutex_t _LockData;
	int _sock;
	RecvData *_recvDataUdp;
	RecvData *_recvDataBuf;
	RecvData *_recvDataBufLast;
	sem_t _taskSem;

	pthread_t _bufServerPid;
	pthread_t _recvServerPid;
	pthread_t _sendServerTid;


private:
	int _mmsgRecvNum;
	struct mmsghdr _msgVec[UDP_REV_MMSG_NUM];
	RecvData** _mmsgRecvBuf;
	//struct sockaddr_in _mmsg_msg_name[UDP_REV_MMSG_NUM];
	struct iovec _mmsg_msg_iov[UDP_REV_MMSG_NUM];

	int _mmsgSendNum;
	struct mmsghdr _mmsgSendVec[UDP_SND_MMSG_NUM];
	struct sockaddr_in _mmsgSendName[UDP_SND_MMSG_NUM];
	struct iovec _mmsgSendIov[UDP_SND_MMSG_NUM];
	unsigned char _mmsgSendIovBase[UDP_SND_MMSG_NUM][UDP_BUF_SIZE];
};

} //namespace net 
} //namespace peace 


#endif

