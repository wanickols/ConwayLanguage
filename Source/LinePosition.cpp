#include "pch.h"
#include "LinePosition.h"

LinePosition::LinePosition(int index, int line, int column, string& file_name) : index(index), line(line), column(column), fileName(file_name)
{
}

//Increments Position
void LinePosition::Advance(const char& currentChar)
{
	++index;
	++column;

	if (currentChar == '\n') 
	{
		++line;
		column = 0;
	}
}

LinePosition LinePosition::copy()
{
	return LinePosition(index, line, column, fileName);
}