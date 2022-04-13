
#pragma once

#include "Token.h"
#include "Error.h"
#include "LinePosition.h"

class Lexer
{
public:
	//Constructor
	Lexer(std::string& inputText, std::string& fileName);
	

	//Functions
	void advance(); //advances character
	void make_tokens(); //makes tokens based on custom tokens class
	Token make_number(); //makes a number based on digits and dots
	
	//Accessors
	const LinePosition& getPos() const; //returns pos
	const vector<Token>& getTokens() const; //returns tokens after made

private:
	//Variables
	LinePosition pos;
	std::string text;
	char currentChar;
	vector<Token> tokens;
};
