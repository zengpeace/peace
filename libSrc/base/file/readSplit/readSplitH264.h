#ifndef _READ_SPLIT_H264_
#define _READ_SPLIT_H264_ 

#include "readSplitBase.h"

namespace peace
{
namespace base
{

class ReadSplitH264 : public ReadSplitBase
{
private:
	virtual	int split(unsigned char *data, const int dataSize, unsigned char* &frameData, int &frameSize) const;
};

} //namespace base 
} //namespace peace 


#endif 

