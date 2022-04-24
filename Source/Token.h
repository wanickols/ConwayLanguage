#pragma once

#include "LinePosition.h"

const enum tokenTypes
{
	T_PLUS = 0,
	T_MINUS,
	T_MULTIPLY,
	T_DIVIDE,
	T_LEFTPAR,
	T_RIGHTPAR,
	T_INT,
	T_FLOAT,
	T_POW,
	T_EOF
};

class Token
{
public:


	Token(tokenTypes type, int value = NULL, std::shared_ptr<LinePosition> pos_start = nullptr, std::shared_ptr<LinePosition> pos_end = nullptr);
	Token(tokenTypes type, float value = NULL, std::shared_ptr<LinePosition> pos_start = nullptr, std::shared_ptr<LinePosition> pos_end = nullptr);

	std::string Representation();
	
	//Accessors
	tokenTypes getType() const;
	const std::shared_ptr<LinePosition> getPosStart() const;
	const std::shared_ptr<LinePosition> getPosEnd() const;

	//Variables
	int value = NULL;
	float fvalue = NULL;
private:
	tokenTypes type;
	string empt;

	LinePosition posStart;
	LinePosition posEnd;
};


