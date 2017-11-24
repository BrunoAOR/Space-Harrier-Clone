#ifndef H_GLOBALS
#define H_GLOBALS

#define OutputLog(format, ...) outputLog(__FILE__, __LINE__, format, __VA_ARGS__)


void outputLog(const char file[], int line, const char* format, ...);


#endif // H_GLOBALS
