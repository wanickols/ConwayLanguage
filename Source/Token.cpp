#include "pch.h"
#include "Token.h"
#include "LinePosition.h"

//Int
Token::Token(tokenTypes type, int value, std::shared_ptr<LinePosition> pos_start, std::shared_ptr<LinePosition> pos_end) : type(type), value(value), empt("nothing"), posStart(0, 0, 0, empt), posEnd(0, 0, 0, empt)
{

	if (pos_start != nullptr) {
		posStart = *pos_start;

		if (pos_end == nullptr) {
			posStart = posStart;
			++posEnd.column;
		}
		else 
		{
			posEnd = *pos_end;
		}
	}

}

//Float
Token::Token(tokenTypes type, float value, std::shared_ptr<LinePosition> pos_start, std::shared_ptr<LinePosition> pos_end) : type(type), fvalue(value), posStart(0, 0, 0, empt), posEnd(0, 0, 0, empt)
{
	
	if (pos_start != nullptr) {
		posStart = *pos_start;

		if (pos_end == nullptr) {
			posStart = posStart;
			++posEnd.column;
		}
		else
		{
			posEnd = *pos_end;
		}
	}
}

Token::Token(tokenTypes type, string value, std::shared_ptr<LinePosition> pos_start, std::shared_ptr<LinePosition> pos_end) : type(type), svalue(value), posStart(0, 0, 0, empt), posEnd(0, 0, 0, empt)
{
}

//Repr
std::string Token::Representation()
{

	const char* typesString[]
	{
		"PLUS",
		"MINUS",
		"MULTIPLY",
		"DIVIDE",
		"LEFTPAR",
		"RIGHTPAR",
		"INT",
		"FLOAT",
		"TOPOWEROF",
		"EQUALS",
		"IDENTIFIER",
		"KEYWORD",
		"EOF"
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

const std::shared_ptr<LinePosition> Token::getPosStart() const
{
	return std::make_shared<LinePosition>(posStart);
}

const std::shared_ptr<LinePosition> Token::getPosEnd() const
{
	return std::make_shared<LinePosition>(posStart);
}
