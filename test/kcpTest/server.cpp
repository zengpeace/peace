#include "base.h"


int main()
{
	Base *b1 = Base::create("0.0.0.0", 1937, 0, "server", (void*)"/home/z/ktest/recv.h264");
	if(b1 == nullptr)
	{
		LOGD("server create fail !\n");
		return -1;
	}	

	/*Base *b2 = Base::create("127.0.0.1", 12002, 0, "client", (void*)"/work/job/videoTrans/send.h264");
	if(b2 == nullptr)
	{
		LOGD("client create fail !\n");
		return -2;
	}*/	
	
	//for(;;)
	{
		sleep(30);
	}

	delete b1;
	b1 = NULL;
	return 0;
}


