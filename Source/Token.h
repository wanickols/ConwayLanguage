#pragma once

const enum tokenTypes
{
	T_PLUS = 0,
	T_MINUS,
	T_MULTIPLY,
	T_DIVIDE,
	T_LEFTPAR,
	T_RIGHTPAR,
	T_INT,
	T_FLOAT
};


class Token
{
public:


	Token(tokenTypes type, int value = NULL, int pos_start = NULL, int pos_end = NULL);
	Token(tokenTypes type, float value = NULL, int pos_start = NULL, int pos_end = NULL);

	std::string Representation();
	
	//Accessors
	tokenTypes getType() const;
	const int getPosStart() const;
	const int getPosEnd() const;

private:
	tokenTypes type;
	int value = NULL;
	float fvalue = NULL;

	int posStart;
	int posEnd;
};


