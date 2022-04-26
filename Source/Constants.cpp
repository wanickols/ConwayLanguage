#include "pch.h"
#include "Constants.h"

Keywords::Keywords()
{

	for (auto const& word : keywordList)
		++keywordsMap[word];

}

bool Keywords::isKeyword(const string input)
{
	if (keywordsMap.find(input) != keywordsMap.end())
		return true;

	return false;
}
