#ifndef _READ_SPLIT_AAC_H_
#define _READ_SPLIT_AAC_H_ 

#include "readSplitBase.h"


namespace peace 
{
namespace base 
{

class ReadSplitAAC : public ReadSplitBase 
{
private:
	virtual	int split(unsigned char *data, const int dataSize, unsigned char* &frameData, int &frameSize) const;

};

} //namespace base 
} //namespace peace 


#endif


