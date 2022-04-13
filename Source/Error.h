#pragma once

using namespace std;

class LinePosition;

class Error
{
public:

	//Constructor
	Error(string error_name, string details, LinePosition& pos);

	//Functions
	string as_string();
	

private:
	//Variables
	string details;
	string errorName;
	LinePosition& pos;
};


class IllegalCharError : public Error
{
public:

	//Constructor
	IllegalCharError(string details, LinePosition& pos);

};