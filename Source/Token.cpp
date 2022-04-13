#include "pch.h"
#include "Token.h"

Token::Token(tokenTypes type, int value) : type(type), value(value)
{
}

Token::Token(tokenTypes type, float value) : type(type), fvalue(value)
{
}

std::string Token::Representation()
{

	const char* typesString[8]
	{
		"PLUS",
		"MINUS",
		"MULTIPLY",
		"DIVIDE",
		"LEFTPAR",
		"RIGHTPAR",
		"INT",
		"FLOAT"
	};

	std::stringstream rpr;
	rpr << typesString[type];
	if (value != NULL) {
		rpr << ":" << value;
	}
	else if (fvalue != NULL)
		rpr << ":" << fvalue;
	rpr << " ";
	return rpr.str();

}
