#include "base/file/file.h"


namespace peace 
{
namespace base 
{

void fileSimpleWrite(const unsigned char *data, const int size, const char *fileAbsName)
{
    if(!fileAbsName)
    {
        return;
    }

    SaveFile *s = SaveFile::getObj(fileAbsName);
	if(!s)
	{
		s = new SaveFile();
		if(!s)
		{
			LOGD("new error !\n");
			return;
		}

		void *tmp = s->open(fileAbsName);
		if(!tmp)
		{
			LOGD("open fail !\n");
			return;
		}
	}
		
	s->wr(data, size);
}

void fileSimpleClose(const char *fileAbsName)
{
	if(!fileAbsName)
	{
		return;
	}

	SaveFile *s = SaveFile::getObj(fileAbsName);
	if(s)
	{
		delete s;
	}
}


void fileReadSplitH264(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize)	
{
	ReadSplitBase *r = ReadSplitBase::create("h264");
	if(!r)
	{
		LOGD("new ReadSplitH264 fail !\n");
		return;
	}

	r->deal(fileAbsName, dealFunc, arg, readBuf, readBufSize);
}

void fileReadSplitAAC(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize)	
{
	ReadSplitBase *r = ReadSplitBase::create("aac");
	if(!r)
	{
		LOGD("new ReadSplitAAC fail !\n");
		return;
	}

	r->deal(fileAbsName, dealFunc, arg, readBuf, readBufSize);
}

} //namespace base
} //namespace peace


