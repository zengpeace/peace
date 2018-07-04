#ifndef _PEACE_TYPES_H_
#define _PEACE_TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>
#include <syslog.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <map>


#define THREAD_STACK_SIZE_SMALL		(16 * 1024)
#define THREAD_STACK_SIZE_MIDDLE	(1 * 1024 * 1024)
#define THREAD_STACK_SIZE_LARGE		(16 * 1024 * 1024)

#define UDP_BUF_SIZE 	1500
#define CHAIN_SIZE 		(4 * 1024)

#define  EPOLL_MAX_EVENT 1000

typedef struct 
{
	struct epoll_event events[EPOLL_MAX_EVENT + 1];
	int nevents;
	int epfd;
}Epollop;

typedef struct _recvData
{
	int count;
	unsigned char buf[UDP_BUF_SIZE];
	struct sockaddr_in addr;
	struct _recvData *pNext;
}RecvData;

typedef struct _BufferInfo 
{
        unsigned char *pData;
        int nSize;
        int nFlag;
        struct _BufferInfo *pNext;
}BufferInfo;

typedef struct
{
        sem_t m_Semaphore;
        pthread_mutex_t m_Lock;
        BufferInfo *m_Push;
        BufferInfo *m_Pop;
        BufferInfo *m_pInfo;
        unsigned char *m_pData;
        unsigned char *m_pCurr;
        int m_nInfoSize;
        int m_nDataSize;
}BlockInfo;

typedef enum 
{
	eUdpServer,
	eUdpClient,
}UdpUserType;

typedef int (*UdpBusinessDealFuncType)(void *udp, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr);
typedef int (*TcpBusinessDealFuncType)(void *tcp, const unsigned char *data, const int dataSize, const int sock);


#define LOGD printf



static const int gUdpClientSelfPortRangeBegin = 40001;
static const int gUdpClientSelfPortRangeEnd = 45000;

static const int gSockBufSize = 256 * 1024;

#endif



