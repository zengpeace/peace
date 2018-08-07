#include "client.h"


int Client::initExLogic(void* initExlogicArgs)
{
	char *fileAbsName = (char*)initExlogicArgs;
	_fileAbsName = fileAbsName;

	_fp = fopen("/work/job/videoTrans/client.h264", "wb");

	_isRunning = true;
	threadCreateSmall(_readSendTid, this->readSendThread, (void*)this);
	return 0;
}

void Client::exitExLogic()
{
	_isRunning = false;
	threadClose(_readSendTid);

	if(_fp)
	{
		fclose(_fp);
	}
}

int Client::_kcpRecvFunc(const char *buf, const int len, ikcpcb *kcp)
{
	LOGD("client recv package, dataSize is %d\n", len);
	return 0;
}

void* Client::readSendThread(void* arg)
{
	Client *c = (Client*)arg;
	c->_readSendThread();
	return NULL;
}

void Client::_readSendThread()
{
	while(_isRunning)
	{
		mediaReadSplitH264(_fileAbsName.c_str(), this->getOneFrame, (void*)this, _buf, _bufSize);
		//mediaReadSplitH264(_fileAbsName.c_str(), this->testSplit, (void*)this, _buf, _bufSize);

		LOGD("prepare to close local tmp file !\n");
		fclose(_fp);

		while(_isRunning)
		{
			sleep(10);
		}
	}
}

void Client::getOneFrame(const unsigned char *data, const int dataSize, void* arg)
{
	Client *c = (Client*)arg;
	c->_getOneFrame(data, dataSize);
} 

void Client::_getOneFrame(const unsigned char *data, const int dataSize)
{
	static int idx = 0;
	unsigned char sign = data[4] & 0x1F;
	if(sign != 0x08 && sign != 0x07 && sign != 0x06)
	{
		idx ++;
		//LOGD("idx = %d\n", idx);
	}
	
	LOGD("%d:dataSize %d\n", idx, dataSize);
	fwrite(data, 1, dataSize, _fp);
	_kcp.sendPackage(data, dataSize);
}


void Client::testSplit(const unsigned char *data, const int dataSize, void* arg)
{
	//LOGD("split dataSize is %d\n", dataSize);
}

