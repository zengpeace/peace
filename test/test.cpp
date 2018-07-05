#include "peaceInterface.h"


int server(void *udp, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	LOGD("into %s ! dataSize is %d\n", __FUNCTION__, dataSize);	
	return netSend(udp, data, dataSize, peerAddr);
} 

int client(void *udp, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	LOGD("into %s ! dataSize is %d\n", __FUNCTION__, dataSize);	
	//return netSend(udp, data, dataSize, peerAddr);
	return 0;
}

int main()
{
	/*unsigned char buf[99] = {48};
	unsigned char buf2[99] = {49};
	for(int i = 0; i < 10; i ++)
	{
		fileSimpleWrite(buf, 98, "test1.txt");
		fileSimpleWrite(buf2, 98, "test2.txt");
	}

	fileSimpleClose("test1.txt");
	fileSimpleClose("test2.txt");*/ 

	
	void* us = netCreate("udpServer");
	netRegisterUdpBusFunc(us, server);
	netSetUseSendThread(us);	
 	netStart(us, "0.0.0.0", 9876);

	void* uc = netCreate("udpClient");
	netRegisterUdpBusFunc(uc, client);
	netSetUseSendThread(uc);
	netStart(uc, "127.0.0.1", 9876);	

	unsigned char data[] = {1, 3, 5};
	netSend(uc, data, sizeof(data)/sizeof(unsigned char));	

	for(;;)
	{
		sleep(10);
	}

	return 0;
}


