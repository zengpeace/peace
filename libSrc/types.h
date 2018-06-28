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
#include <sys/poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <map>


#define UDP_BUF_SIZE 1400

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


typedef int (*NetBusinessDealFuncType)(const unsigned char *data, const int dataSize);



#define LOGD printf
#endif

