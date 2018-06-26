#ifndef _PEACE_BASE_FILE_FILE_H_
#define _PEACE_BASE_FILE_FILE_H_ 


#include "simpleSaveFile.h"


namespace peace 
{
namespace base 
{

void fileSimpleWrite(const unsigned char *data, const int size, const char *fileAbsName);
void fileSimpleClose(const char *fileAbsName);

} //namespace base
} //namespace peace



#endif

