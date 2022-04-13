#include "pch.h"
#include "Lexer.h"

const string digits = "0123456789";

//Constructor
Lexer::Lexer(std::string& text, std::string& fileName) : text(text), pos(-1,0,-1, fileName), currentChar(0)
{
	//Pos is -1 because advance will immedietly increment it.
	advance();
}

//Functions
void Lexer::advance()
{
	pos.Advance(currentChar);
	if (pos.index < text.length()) //if still have text
		currentChar = text[pos.index];
	else
	{
		pos.index = -1; //No value
		currentChar = NULL;
	}
}

void Lexer::make_tokens()
{
	while (currentChar != NULL)
	{


		if (isspace(currentChar)) //if current char is space then just adavnce
		{
			advance();
		}
		else if (digits.find(currentChar) != string::npos) //digits contains it, then its a number
		{
			tokens.push_back(make_number());
		}
		else {

			switch (currentChar)
			{
			case '+':
				tokens.push_back(Token(tokenTypes::T_PLUS, NULL));
				break;
			case '-':
				tokens.push_back(Token(tokenTypes::T_MINUS, NULL));
				break;
			case '*':
				tokens.push_back(Token(tokenTypes::T_MULTIPLY, NULL));
				break;
			case '/':
				tokens.push_back(Token(tokenTypes::T_DIVIDE, NULL));
				break;
			case '(':
				tokens.push_back(Token(tokenTypes::T_LEFTPAR, NULL));
				break;
			case ')':
				tokens.push_back(Token(tokenTypes::T_RIGHTPAR, NULL));
				break;
			default:
				char c = currentChar;
				stringstream ss;
				ss << "'" << c << "'";
				IllegalCharError error(ss.str(), pos);
				cout << error.as_string(); //Logs errror
				break;

			}
			advance();
		}
	}
}

Token Lexer::make_number()
{
	stringstream num_str;
	short dot_count = 0;

	while (currentChar != NULL && (digits.find(currentChar) != string::npos || currentChar == '.'))
	{
		if (currentChar == '.')
		{
			if (dot_count == 1)
				break;
			++dot_count;
			num_str << '.';
		}
		else
		{
			num_str << currentChar;
		}
		advance();
	}

	if (dot_count == 0)
	{
		int x;
		num_str >> x;
		return Token(tokenTypes::T_INT, x);
	}
	else
	{
		float f;
		num_str >> f;
		return Token(tokenTypes::T_FLOAT, f);
	}
}


//Accessors
const LinePosition& Lexer::getPos() const
{
	return pos;
}

const vector<Token>& Lexer::getTokens() const
{
	if (tokens.empty())
		throw("Error tokens called but not found");

	return tokens;
}
