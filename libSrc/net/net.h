#ifndef _PEACE_NET_NET_H_
#define _PEACE_NET_NET_H_ 


namespace peace 
{
namespace base
{

class NetBase 
{
public:
	

	static Net* create(const char *netType, const char *serverOrClient);
	virtual void close() = 0;

private:
		

}

} //namespace base 
} //namespace peace 

#endif

