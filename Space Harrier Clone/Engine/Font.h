#ifndef H_FONT
#define H_FONT

#include <string>
#include <map>
#include "PixelPosition.h"


struct Font
{
public:
	std::string path;
	int characterWidth;
	int characterHeight;
	std::map<char, PixelPosition> charsTopLeftCorners;
};


#endif // !H_FONT
