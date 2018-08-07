#ifndef _CLIENT_H_
#define _CLIENT_H_ 

#include "base.h"

class Client : public Base
{
public:
	virtual int initExLogic(void* initExLogicArgs) override;
	virtual void exitExLogic() override;
	virtual int _kcpRecvFunc(const char *buf, const int len, ikcpcb *kcp) override;

public:
	static void* readSendThread(void* arg);
	void _readSendThread();

	
	static void getOneFrame(const unsigned char *data, const int dataSize, void* arg);
	void _getOneFrame(const unsigned char *data, const int dataSize);
	static void testSplit(const unsigned char *data, const int dataSize, void* arg);

private:
	std::string _fileAbsName;
	FILE *_fp;

	pthread_t _readSendTid;
	bool _isRunning;
};


#endif

