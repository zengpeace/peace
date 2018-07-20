#ifndef _PEACE_BASE_FILE_READ_SPLIT_READ_SPLIT_BASE_H_
#define _PEACE_BASE_FILE_READ_SPLIT_READ_SPLIT_BASE_H_

#include "types.h"

namespace peace
{
namespace base 
{

class ReadSplitBase 
{
public:
	static ReadSplitBase* create(const std::string &fileType);
	void deal(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize) const;	

private:	
	virtual int split(unsigned char *data, const int dataSize, unsigned char* &frameData, int &frameSize) const = 0;
};

} //namespace base 
} //namespace peace 

#endif


