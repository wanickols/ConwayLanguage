#include "pch.h"
#include "Lexer.h"

//Constructor
Lexer::Lexer(std::string& text, std::string& fileName) : text(text), currentChar(0)
{

	pos = std::make_shared<LinePosition>(-1, 0, -1, fileName);
	//Pos is -1 because advance will immedietly increment it.


	
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
	advance();

	while (currentChar)
	{


		if (isspace(currentChar)) //if current char is space then just adavnce
		{
			advance();
		}
		//Numbers
		else if (digits.find(currentChar) != string::npos) //digits contains it, then its a number
		{
			tokens.push_back(make_number());
		}
		//Numbers
		else if (LETTERS.find(currentChar) != string::npos)
		{
			tokens.push_back(makeIdentifier());
		}
		//Symbols
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
			case '^':
				tokens.push_back(Token(tokenTypes::T_POW, NULL, pos));
				break;
			case '=':
				tokens.push_back(makeEqualsOperations());
				break;
			case '!':
				tokens.push_back(makeNotOperations());
				break;
			case '<':
				tokens.push_back(makeLessThanOperations());
				break;
			case '>':
				tokens.push_back(makeGreaterThanOperaitons());
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

	while (currentChar && (digits.find(currentChar) != string::npos || currentChar == '.'))
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

Token Lexer::makeIdentifier()
{
	stringstream ss;
	LinePosition position = *pos;

	while (currentChar && (LETTER_DIGITS.find(currentChar) != string::npos))
	{
		ss << currentChar;
		advance();
	}

	if (keywords.isKeyword(ss.str()))
		return Token(tokenTypes::T_KEYWORD, ss.str(), std::make_shared<LinePosition>(position), pos);

	return Token(tokenTypes::T_IDENTIFIER, ss.str(), std::make_shared<LinePosition>(position), pos);
}

Token Lexer::makeEqualsOperations()
{
	if (GetNextChar() == '=') {
		advance();
		return Token(tokenTypes::T_EE, NULL, pos);
	}
	return Token(tokenTypes::T_EQ, NULL, pos);
}

Token Lexer::makeLessThanOperations()
{

	if (GetNextChar() == '=') {
		advance();
		return Token(tokenTypes::T_LTE, NULL, pos);
	}

	return Token(tokenTypes::T_LT, NULL, pos);
}

Token Lexer::makeGreaterThanOperaitons()
{
	
	if (GetNextChar() == '=') {
		advance();
		return Token(tokenTypes::T_GTE, NULL, pos);
	
	}

	return Token(tokenTypes::T_GT, NULL, pos);
}

Token Lexer::makeNotOperations()
{
	if (GetNextChar() == '=') {
		advance();
		return Token(tokenTypes::T_NE, NULL, pos);
	}

	return Token(tokenTypes::T_NOT, NULL, pos);
}

const char Lexer::GetNextChar()
{
	if (pos->index+1 < text.length()) //if still have text
		return(text[pos->index+1]);
	else
	{
		CW_CORE_WARN("No Char Found After Operator " + pos->represent());
		return('f');
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

void Lexer::setText(string& text)
{
	this->text = text;
}
