#include "base/file/simpleSaveFile.h"

namespace peace 
{
namespace base 
{

SaveFileFpMap mapFp;

SaveFile::~SaveFile()
{
	this->close();
}

SaveFile* SaveFile::getObj(const char *fileName)
{
	if(!fileName)
	{
		return NULL;
	}

	SaveFileFpMap::iterator mapFpIt;
    mapFpIt = mapFp.find(fileName);
    if (mapFpIt != mapFp.end())
    {
        return (SaveFile*)mapFpIt->second;
    }
	
	return NULL;
}

void *SaveFile::open(const char *fileName)
{
	if (!fileName)
	{
		return NULL;
	}

	_fp = fopen(fileName, "wb");
	void *me = (void*)this;
	mapFp.insert(std::make_pair(fileName, me));
	LOGD("open file %s\n", fileName);
	return me;
}

void SaveFile::wr(const void *data, const int dataSize)
{
	if (!data || dataSize <= 0)
	{
		return;
	}

	if (_fp)
	{
		fwrite(data, dataSize, 1, _fp);
	}
}

void SaveFile::close()
{
	if (_fp)
	{
		SaveFileFpMap::iterator mapFpIt = mapFp.begin();
		while (mapFpIt != mapFp.end())
		{
			if (mapFpIt->second == _fp)
			{
				mapFp.erase(mapFpIt);
			}
			
			mapFpIt++;
		}

		fclose(_fp);
		_fp = NULL;
	}
}

} //namespace base
} //namespace peace 

