#pragma once

using namespace std;

class LinePosition;
class Context;

class Error
{
public:

	//Constructor
	Error(string error_name, string details, std::shared_ptr<LinePosition> pos);

	//Functions
	virtual string as_string();
	

protected:
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

class RTError : public Error
{
public:

	//Constructor
	RTError(string details, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context);
	string as_string() override;

private:
	std::shared_ptr<Context> context;
};