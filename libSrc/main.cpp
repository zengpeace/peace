#include "peaceInterface.h"


int server(void *udp, const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr, void* arg)
{
	LOGD("into %s ! dataSize is %d\n", __FUNCTION__, dataSize);	
	if(dataSize > 0)
	{
		for(int i = 0; i < 8; i ++)
		{
			LOGD("%d ", data[i]);
		}
	}
	LOGD("\n");

	return netSend(udp, data, dataSize, peerAddr);
} 

int main()
{
	void* us = netCreate("udpServer", NULL, true);
	netRegisterUdpBusFunc(us, server);
	netSetUseSendThread(us);	
 	netStart(us, "0.0.0.0", 9876);
	
	for(;;)
	{

	}
}


