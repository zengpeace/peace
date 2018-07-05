#ifndef _PEACE_BASE_FILE_SIMPLE_SAVE_FILE_H_
#define _PEACE_BASE_FILE_SIMPLE_SAVE_FILE_H_ 

#include "types.h"

namespace peace 
{
namespace base 
{

typedef std::map<const char*, void*> SaveFileFpMap;

class SaveFile
{
public:
	~SaveFile();
	static SaveFile* getObj(const char *fileName); 
	void * open(const char *fileName);
	void wr(const void *data, const int dataSize);
	void close();
private:
	FILE * _fp;
};

} //namespace base
} //namespace peace

#endif

