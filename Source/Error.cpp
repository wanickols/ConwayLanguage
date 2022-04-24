#include "pch.h"
#include "Error.h"
#include "LinePosition.h"
#include "Context.h"

//##########ERROR##############

//Constructor
Error::Error(string error_name, string details, std::shared_ptr<LinePosition> pos) : errorName(error_name), details(details), pos(pos)
{
}

//Functions
string Error::as_string()
{
	stringstream ss;
	ss << errorName << ": " << details << pos->represent();
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

RTError::RTError(string details, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context) : Error("Runtime Error", details, pos), context(context)
{
}

string RTError::as_string()
{
	stringstream ss;
	ss << errorName << ": " << details << "Context: " << context->represent() << pos->represent();
	return ss.str();
}
