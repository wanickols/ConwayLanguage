#pragma once

//TokeTypes
static const enum tokenTypes
{
	T_PLUS = 0,
	T_MINUS,
	T_MULTIPLY,
	T_DIVIDE,
	T_LEFTPAR,
	T_RIGHTPAR,
	T_LEFTBRAK,
	T_RIGHTBRAK,
	T_COMMA,
	T_INT,
	T_FLOAT,
	T_POW,
	T_EQ,
	T_EE,
	T_NOT,
	T_NE,
	T_LT,
	T_GT,
	T_LTE,
	T_GTE,
	T_IDENTIFIER,
	T_KEYWORD,
	T_EOF
};

//Token Representation Words
static const char* typesString[]
{
	"PLUS", //+
	"MINUS", //-
	"MULTIPLY", //*
	"DIVIDE", // /
	"LEFTPAR", //(
	"RIGHTPAR", //)
	"LEFTBRAK",
	"RIGHTBRAK",
	"INT", // Any Number e.g. 5
	"FLOAT", // Any decimal number e.g 5.2
	"TOPOWEROF", // ^
	"EQUALS", // =
	"ISEQUAL", // ==
	"NOT", //! or NOT
	"ISNOTEQUAL", // !=
	"ISLESS", // <
	"ISGREATER", // >
	"ISLESS|ISQEUAL", // <=
	"ISGREATER|ISEQUAL", // >=
	"IDENTIFIER", // Any word
	"KEYWORD", // Word of keywords
	"EOF" // No representation, end of file. 
};

//Letter comparison variables
const string digits = "0123456789";
const string LETTERS = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string LETTER_DIGITS = digits + LETTERS;

//Keywords
static const std::vector<string> keywordList
{
	"Int",
	"AND",
	"OR",
	"NOT",
	"Float",
	"Cell",
	"IF",
	"THEN",
	"ELIF",
	"ELSE",
	"WHILE",
	"FOR",
	"STEP",
	"TO"
};

//Variable types
const enum VARIABLE_TYPES
{
	Int = 0,
	Float,
	Cell
};

//Keyword Class that contains and hashes keywords
class Keywords
{
public:
	Keywords();

	bool isKeyword(const string input);

private:
	std::unordered_map<string, int> keywordsMap;

};

