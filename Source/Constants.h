#pragma once



//TokeTypes
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
	T_EQUALS,
	T_IDENTIFIER,
	T_KEYWORD,
	T_EOF
};


//Letter comparison variables
const string digits = "0123456789";
const string LETTERS = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string LETTER_DIGITS = digits + LETTERS;

const std::vector<string> keywordList
{
	"Int",
	"Float",
	"Cell",
	"If",
	"While",
	"For"
};

const enum VARIABLE_TYPES
{
	Int = 0,
	Float,
	Cell
};

//Keyword INit
class Keywords
{
public:
	Keywords();

	bool isKeyword(const string input);

private:
	std::unordered_map<string, int> keywordsMap;

};

