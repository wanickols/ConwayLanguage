#pragma once

#include "Token.h"
#include "Node.h"


class NumberNode;
class BinOpNode;

class Parser
{
public:
	Parser(vector<Token>& tokens);

	void advance();

	std::shared_ptr<Node> parse();



private:
	vector<Token>& tokens;
	std::shared_ptr<vector<Node>> nodes;
	unsigned int tok_idx;
	Token* currentToken;
	//int parseCounter;
	//int binOpCounter;

	std::shared_ptr<unordered_set<string>> BinKeywords;

	//Parser Definitions
	std::shared_ptr<Node> atom(); //Most basic value
	std::shared_ptr<Node> power(); //Power rules
	std::shared_ptr<Node> factor(); //Addition of Atoms or Powers
	std::shared_ptr<Node> term(); //Multiplication of Factors
	std::shared_ptr<Node> arith_expr(); //Addition of Terms
	std::shared_ptr<Node> cmpr_expr(); //Comparisons of Arithmetic Expressions
	std::shared_ptr<Node> expr(); //Logical Expression
	std::shared_ptr<Node> if_expr(); //Logical Expression
	std::shared_ptr<Node> for_expr(); //Logical Expression
	std::shared_ptr<Node> while_expr(); //Logical Expression


	std::shared_ptr<Node> returnNotExpr();

	std::shared_ptr<Node> throwError(std::string details);

	std::shared_ptr<Node> bin_op(std::function<std::shared_ptr<Node>()>, std::shared_ptr<unordered_set<tokenTypes>> ops, std::function<std::shared_ptr<Node>()> func2 = NULL);
	std::shared_ptr<Node> bin_op_key(std::function<std::shared_ptr<Node>()>, std::shared_ptr<unordered_set<string>> ops, std::function<std::shared_ptr<Node>()> func2 = NULL);
	
};

