#ifndef _PEACE_NET_UDP_UDP_H_
#define _PEACE_NET_UDP_UDP_H_ 


#include "net/base/netBase.h"

namespace peace 
{
namespace net 
{

class Udp : public NetBase  
{
public:
	Udp();
	~Udp();	

private:
	int testData;

};

} //namespace net 
} //namespace peace 


#endif

