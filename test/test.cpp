#include "peaceInterface.h"


int server(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{
	

} 

int client(const unsigned char *data, const int dataSize, const struct sockaddr_in &peerAddr)
{

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
	registerUdpBusFunc(us, server);	
 	netStart(us, "0.0.0.0", 9876);

	void* uc = netCreate("udpClient");
	registerUdpBusFunc(uc, client);
	netStart(uc, "127.0.0.1", 9876);	

	

	return 0;
}

