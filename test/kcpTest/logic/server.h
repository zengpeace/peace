#ifndef _SERVER_H_
#define _SERVER_H_

#include "base.h"

class Server : public Base 
{
public:
	int initExLogic(void* initExlogicArgs) override;
	void exitExLogic() override;
	virtual int _kcpRecvFunc(const char *buf, const int len, ikcpcb *kcp) override;

private:
	FILE* _fp;
};


#endif

