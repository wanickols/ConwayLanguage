#pragma once

#include "LinePosition.h"

class Token
{
public:


	Token(tokenTypes type, int value = NULL, std::shared_ptr<LinePosition> pos_start = nullptr, std::shared_ptr<LinePosition> pos_end = nullptr);
	Token(tokenTypes type, float value = NULL, std::shared_ptr<LinePosition> pos_start = nullptr, std::shared_ptr<LinePosition> pos_end = nullptr);
	Token(tokenTypes type, string value = NULL, std::shared_ptr<LinePosition> pos_start = nullptr, std::shared_ptr<LinePosition> pos_end = nullptr);

	std::string Representation();
	
	//Accessors
	tokenTypes getType() const;
	const std::shared_ptr<LinePosition> getPosStart() const;
	const std::shared_ptr<LinePosition> getPosEnd() const;

	//Variables
	int value = NULL;
	float fvalue = NULL;
	string svalue = " ";
private:
	tokenTypes type;
	string empt;

	LinePosition posStart;
	LinePosition posEnd;
};


