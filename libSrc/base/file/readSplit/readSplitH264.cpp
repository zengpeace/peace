#include "readSplitH264.h"


namespace peace 
{
namespace base 
{

int ReadSplitH264::split(unsigned char *data, const int dataSize, unsigned char* &frameData, int &frameSize) const
{
	bool fourBytes = true;
	int tmpSize;
	int tmpStartIndex = 0;
	unsigned char *pTmp = NULL;
	for(int i = 0; i < dataSize - 4; i ++)
	{
		if(data[i] == 0 && data[i + 1] == 0 && data[i + 2] == 1)
		{
			if(pTmp)
			{
				tmpSize = i - tmpStartIndex;
				if(i > 0 && data[i - 1] == 0)
				{
					tmpSize --;
				}

				frameSize = tmpSize + 3;
				frameData = pTmp;
				if(fourBytes)
				{
					frameData -= 4;
					frameSize += 4;
				}
				else 
				{
					frameData -= 3;
					frameSize += 3;
				}
				return 1;
			}

			if(i > 0 && data[i - 1] == 0)
			{
				fourBytes = true;
			}
			else 
			{
				fourBytes = false;
			}

			tmpStartIndex = i + 3;
			pTmp = data + tmpStartIndex;
		}
	}

	tmpSize = 0;
	if(pTmp)
	{
		tmpSize = data + dataSize - pTmp;
		frameSize = tmpSize;
		frameData = pTmp;
		if(fourBytes)
		{
			frameData -= 4;
			frameSize += 4;
		}
		else 
		{
			frameData -= 3;
			frameSize += 3;
		}
		
		return 0;
	}
	
	return -1;
}


} //namespace base 
} //namespace peace 

