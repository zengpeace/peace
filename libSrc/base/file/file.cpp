#include "file.h"


namespace peace 
{
int b = 3;
namespace base 
{

int a = 2;

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
		if(tmp)
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

} //namespace base
} //namespace peace


