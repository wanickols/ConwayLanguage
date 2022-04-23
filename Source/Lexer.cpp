#include "pch.h"
#include "Lexer.h"

const string digits = "0123456789";

//Constructor
Lexer::Lexer(std::string& text, std::string& fileName) : text(text), currentChar(0)
{

	pos = std::make_shared<LinePosition>(-1, 0, -1, fileName);
	//Pos is -1 because advance will immedietly increment it.
	advance();

	
}

//Functions
void Lexer::advance()
{
	pos->Advance(currentChar);
	if (pos->index < text.length()) //if still have text
		currentChar = text[pos->index];
	else
	{
		pos->index = -1; //No value
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
				tokens.push_back(Token(tokenTypes::T_PLUS, NULL, pos));
				break;
			case '-':
				tokens.push_back(Token(tokenTypes::T_MINUS, NULL, pos));
				break;
			case '*':
				tokens.push_back(Token(tokenTypes::T_MULTIPLY, NULL, pos));
				break;
			case '/':
				tokens.push_back(Token(tokenTypes::T_DIVIDE, NULL, pos));
				break;
			case '(':
				tokens.push_back(Token(tokenTypes::T_LEFTPAR, NULL, pos));
				break;
			case ')':
				tokens.push_back(Token(tokenTypes::T_RIGHTPAR, NULL, pos));
				break;
			default:
				char c = currentChar;
				stringstream ss;
				ss << "'" << c << "'";
				IllegalCharError error(ss.str(), pos);
				CW_CORE_ERROR(error.as_string()); //Logs errror
				break;

			}
			advance();
		}
	}
	tokens.push_back(Token(tokenTypes::T_EOF, NULL, pos));
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
		return Token(tokenTypes::T_INT, x, pos);
	}
	else
	{
		float f;
		num_str >> f;
		return Token(tokenTypes::T_FLOAT, f, pos);
	}
}


//Accessors
const std::shared_ptr<LinePosition> Lexer::getPos() const
{
	return pos;
}

const vector<Token>& Lexer::getTokens() const
{
	if (tokens.empty()) {
		CW_CORE_ERROR("Tokens called but not found");
		exit(-1);
	}
	return tokens;
}
