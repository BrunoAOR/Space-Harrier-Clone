#ifndef H_SCORE_INFO
#define H_SCORE_INFO

#include <string>

#include "Engine/globals.h"
struct ScoreInfo
{
public:
	ScoreInfo(int aScore, const std::string& aName)
		: score(aScore), name(aName) {}
	int score;
	std::string name;
};


#endif // !H_SCORE_INFO
