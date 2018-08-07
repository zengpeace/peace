#include "server.h"

int Server::initExLogic(void* initExLogicArgs)
{
	char *fileAbsName = (char*)initExLogicArgs;
	_fp = fopen(fileAbsName, "wb");
	if(!_fp)
	{
		LOGD("fopen %s wb fail !\n", fileAbsName);
		return -1;
	}

	return 0;	
}

int Server::_kcpRecvFunc(const char *buf, const int len, ikcpcb *kcp)
{
	static int idx = 0;
	unsigned char sign = buf[4] & 0x1F;
	if(sign != 0x08 && sign != 0x07 && sign != 0x06)
	{
		idx ++;
	}

	LOGD("%d:	%d\n", idx, len);	
	return fwrite(buf, 1, len, _fp);	
}

void Server::exitExLogic()
{
	if(_fp)
	{
		fclose(_fp);
		_fp = NULL;
	}
}



