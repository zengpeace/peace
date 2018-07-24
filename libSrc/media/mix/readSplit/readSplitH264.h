#ifndef _PEACE_BASE_FILE_READ_SPLIT_READ_SPLIT_H264_H_
#define _PEACE_BASE_FILE_READ_SPLIT_READ_SPLIT_H264_H_

#include "readSplitBase.h"

namespace peace
{
namespace media
{

class ReadSplitH264 : public ReadSplitBase
{
private:
	virtual	int split(unsigned char *data, const int dataSize, unsigned char* &frameData, int &frameSize) const override;
};

} //namespace media 
} //namespace peace 


#endif 

