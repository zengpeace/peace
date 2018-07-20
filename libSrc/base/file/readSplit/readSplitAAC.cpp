#include "readSplitAAC.h"

namespace peace 
{
namespace base
{

int ReadSplitAAC::split(unsigned char *data, const int dataSize, unsigned char* &frameData, int &frameSize) const 
{
	if (!data || dataSize < 7) 
    {
        return -1;
    }

    unsigned char *pStart = NULL;
    int startIndex, size = 0;
    for (int i = 0; i < dataSize; i++)
    {   
        if (data[i] == 0xFF && (data[i + 1] & 0xF6) == 0xF0)
        {
            startIndex = i; 
            pStart = data + startIndex;
            size = ((((unsigned short)pStart[3] & 0x03) << 11) & 0x1800) | \
                (((unsigned short)pStart[4] << 3) & 0x07F8) | \
                (((unsigned short)pStart[5] >> 5) & 0x07);
            break;
        }
    }       
            
    if (size == 0)
    {           
        return -2;
    }       
    else if (size <= dataSize)
    {       
        frameData = pStart;
        frameSize = size; 
        return 1;
    }       
    else    
    {       
        frameData = pStart;
        frameSize = dataSize;
        return 0;
    }

	return -3;
}

} //namespace base 
} //namespace peace

