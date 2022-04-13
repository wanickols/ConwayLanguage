#pragma once
class LinePosition
{
public:

	//Constructor
	LinePosition(int index, int line, int column, string& file_name);

	//Functions
	void Advance(const char& currentChar);
	LinePosition copy();

	//Variables
	int index; //current char number
	int line; //current line number
	int column; //current column number
	string fileName;
};

