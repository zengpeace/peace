#include "readSplitBase.h"
#include "readSplitH264.h"
#include "readSplitAAC.h"

namespace peace 
{
namespace media 
{

ReadSplitBase* ReadSplitBase::create(const std::string &fileType)
{
	ReadSplitBase *base = NULL;
	ReadSplitH264 *h264 = NULL;
	ReadSplitAAC *aac = NULL;
	if(fileType == "h264")
	{
		h264 = new ReadSplitH264();
		if(!h264)
		{
			LOGD("new ReadSplitH264 fail !\n");
			return NULL;
		}
		base = static_cast<ReadSplitBase*>(h264);
	}
	else if(fileType == "aac")
	{
		aac = new ReadSplitAAC();
		if(!aac)
		{
			LOGD("new ReadSplitAAC fail !\n");
			return NULL;
		}
		base = static_cast<ReadSplitBase*>(aac);
	}
	else 
	{
		LOGD("unknow fileType ! %s\n", fileType.c_str());
		return NULL;
	}

	return base;
}

void ReadSplitBase::deal(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize) const
{
	FILE *fp = fopen(fileAbsName, "rb");
	if(!fp)
	{
		LOGD("fopen fail ! %s\n", fileAbsName);
		return;
	}

	if(readBuf && readBufSize <= 4)
	{
		LOGD("readBufSize error ! %d\n", readBufSize);
	}

	unsigned char *buf = NULL;
	int bufSize = 4 * 1024 * 1024;
	if(readBuf)
	{
		buf = readBuf;
		bufSize = readBufSize;
	}
	else 
	{
		buf = new unsigned char[bufSize];
		if(!buf)
		{
			LOGD("new buf fail !\n");
			fclose(fp);
			return;
		}
	}

	unsigned char *pTmp, *pBuf;
	int readBytes, restSize;
	int ret, size;
	bool notFinishRead = true;
	while(notFinishRead)
	{
		readBytes = fread(buf + restSize, 1, bufSize - restSize, fp);
		if(readBytes <= 0)
		{
			notFinishRead = false;
			break;
		}

		pTmp = buf;
		ret = this->split(pTmp, buf + readBytes - pTmp,  pBuf, size);
		if(ret == 1)
		{
			dealFunc(pBuf, size, arg);
			pTmp = pBuf + size;
		}
		else if(ret == 0)
		{
			memcpy(buf, pBuf, size);	
			restSize = size;
			break;
		}
		else 
		{
			notFinishRead = false;
			restSize = 0;
			break;
		}
	}

	if(restSize > 4 && ret == 0)
	{
		dealFunc(pBuf, size, arg);
	}

	if(!readBuf && buf)
	{
		delete buf;
		buf = NULL;
		bufSize = 0;
	}	
}

} //namespace media
} //namespace peace 

