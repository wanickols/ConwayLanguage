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

	Token(tokenTypes type, int value = NULL);
	Token(tokenTypes type, float value = NULL);

	std::string Representation();
	

private:
	tokenTypes type;
	int value = NULL;
	float fvalue = NULL;
};

