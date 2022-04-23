#pragma once

using namespace std;

class LinePosition;

class Error
{
public:

	//Constructor
	Error(string error_name, string details, std::shared_ptr<LinePosition> pos);

	//Functions
	string as_string();
	

private:
	//Variables
	string details;
	string errorName;
	std::shared_ptr<LinePosition> pos;
};


class IllegalCharError : public Error
{
public:

	//Constructor
	IllegalCharError(string details, std::shared_ptr<LinePosition> pos);

};

class IllegalSyntaxError : public Error
{
public:

	//Constructor
	IllegalSyntaxError(string details, std::shared_ptr<LinePosition> pos);

};