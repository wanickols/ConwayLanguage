#include "pch.h"
#include "Error.h"
#include "LinePosition.h"


//##########ERROR##############

//Constructor
Error::Error(string error_name, string details, std::shared_ptr<LinePosition> pos) : errorName(error_name), details(details), pos(pos)
{
}

//Functions
string Error::as_string()
{
	stringstream ss;
	ss << errorName << ": " << details << " | File Name: \"" << pos->fileName << "\" --> Line: " << pos->line + 1 << " Column: " << pos->column << "\n";
	return ss.str();
}

//##########IllegalChar ERROR##############

//Constructor
IllegalCharError::IllegalCharError(string details, std::shared_ptr<LinePosition> pos) : Error("Illegal Character", details, pos)
{
}

IllegalSyntaxError::IllegalSyntaxError(string details, std::shared_ptr<LinePosition> pos) : Error("Illegal Syntax", details, pos)
{
}
