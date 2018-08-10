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

void splitDeal(const unsigned char *data, const int dataSize, void* arg)
{
	//LOGD("dataSize is %d\n", dataSize);
	static int idx = 0;
	FILE *fp = (FILE*)arg;
	fwrite(data, 1, dataSize, fp);

	unsigned char sign = data[4] & 0x1F;
	if(sign != 0x08 && sign != 0x07 && sign != 0x06)
	{
		idx ++;
	}

	LOGD("%d:%d\n", idx, dataSize);
}

int main()
{
	/*void* us = netCreate("udpServer", NULL, true);
	netRegisterUdpBusFunc(us, server);
	//netSetUseSendThread(us);	
 	netStart(us, "0.0.0.0", 9876);

	for(;;)
	{
		sleep(100);
	} */

	/*void *r = mmsgRecvInit("0.0.0.0", 9876);

	for(;;)
	{
		mmsgRecvDo(r);
		sleep(1);
	}
	
	mmsgRecvExit(r);
	r = NULL;*/ 

	FILE *fp = fopen("client.h264", "wb");	

	mediaReadSplitH264("send.h264", splitDeal, (void*)fp, NULL, 0);

	/*for(;;)
	{
		sleep(10);
	}*/

	fclose(fp);

	LOGD("success !\n");
}


