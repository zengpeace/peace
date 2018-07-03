#ifndef _PEACE_BASE_CHAIN_CHAIN_H_
#define _PEACE_BASE_CHAIN_CHAIN_H_ 

#include "types.h"

namespace peace 
{
namespace base 
{
	RecvData *CreateChain(const int len);
	void InsertHead(RecvData **dst, RecvData *src);
	void InsertTail(RecvData **dst, RecvData *src);
	void InsertTailEx(RecvData **dst, RecvData *src, RecvData **dstLast);
	RecvData *GetHeadChain(RecvData **dst);
	void RecoveryChain(RecvData *src, RecvData *recvDataUdp, pthread_mutex_t LockChain);
	void ReleaseChain(RecvData **ppHead);

} //namespace base 
} //namespace peace 

#endif

