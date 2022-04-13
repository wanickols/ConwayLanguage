#include "pch.h"
#include "Error.h"
#include "LinePosition.h"


//##########ERROR##############

//Constructor
Error::Error(string error_name, string details, LinePosition& pos) : errorName(error_name), details(details), pos(pos)
{
}

//Functions
string Error::as_string()
{
	stringstream ss;
	ss << errorName << ": " << details << " | File Name: \"" << pos.fileName << "\" --> Line: " << pos.line + 1 << " Column: " << pos.column + 1 << "\n";
	return ss.str();
}

//##########IllegalChar ERROR##############

//Constructor
IllegalCharError::IllegalCharError(string details, LinePosition& pos) : Error("Illegal Character", details, pos)
{
}
