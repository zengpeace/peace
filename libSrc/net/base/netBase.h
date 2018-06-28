#ifndef _PEACE_NET_BASE_NET_BASE_H_ 
#define _PEACE_NET_BASE_NET_BASE_H_ 

#include "types.h"

namespace peace 
{
namespace net 
{

class NetBase
{
 public:     
	typedef enum 
	{
		eNetTcpServer,
		eNetTcpClient,
		eNetUdpServer,
		eNetUdpClient,
	}NetType;

	NetBase();
	~NetBase();

	static NetBase* create(const NetType type);
	void registerBusinessDealFunc(const NetBusinessDealFuncType pFunc);
	virtual int start(const char *ip, const int port) = 0;
	virtual void stop() = 0;	
 
public:
	NetBusinessDealFuncType _businessDealFunc;


private:


};


} //namespace net 
} //namespace peace 


#endif

