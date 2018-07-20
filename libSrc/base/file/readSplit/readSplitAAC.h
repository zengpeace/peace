#ifndef _PEACE_BASE_FILE_READ_SPLIT_READ_SPLIT_AAC_H_
#define _PEACE_BASE_FILE_READ_SPLIT_READ_SPLIT_AAC_H_

#include "readSplitBase.h"


namespace peace 
{
namespace base 
{

class ReadSplitAAC : public ReadSplitBase 
{
private:
	virtual	int split(unsigned char *data, const int dataSize, unsigned char* &frameData, int &frameSize) const override;

};

} //namespace base 
} //namespace peace 


#endif


