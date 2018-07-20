#ifndef _PEACE_BASE_FILE_FILE_H_
#define _PEACE_BASE_FILE_FILE_H_ 


#include "base/file/simpleSaveFile.h"
#include "base/file/readSplit/readSplitBase.h"


namespace peace 
{
namespace base 
{

void fileSimpleWrite(const unsigned char *data, const int size, const char *fileAbsName);
void fileSimpleClose(const char *fileAbsName);

void fileReadSplitH264(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize);	
void fileReadSplitAAC(const char *fileAbsName, void(*dealFunc)(const unsigned char *data, const int dataSize, void* arg), void* arg, unsigned char *readBuf, const int readBufSize);	

} //namespace base
} //namespace peace



#endif

