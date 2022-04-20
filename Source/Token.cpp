#include "pch.h"
#include "Token.h"

//Int
Token::Token(tokenTypes type, int value, int pos_start, int pos_end) : type(type), value(value), posStart(pos_start), posEnd(pos_end)
{
	if (!posEnd && posStart)
		posEnd = posStart + 1;
}

//Float
Token::Token(tokenTypes type, float value, int pos_start, int pos_end) : type(type), fvalue(value), posStart(pos_start), posEnd(pos_end)
{
}

//Repr
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
	return rpr.str();

}

tokenTypes Token::getType() const
{
	return type;
}

const int Token::getPosStart() const
{
	return posStart;
}

const int Token::getPosEnd() const
{
	return posEnd;
}
