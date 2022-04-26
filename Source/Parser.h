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

	//Parser Definitions

	std::shared_ptr<Node> atom(); 
	std::shared_ptr<Node> power(); 
	std::shared_ptr<Node> factor(); 
	std::shared_ptr<Node> term();  
	std::shared_ptr<Node> expr(); 

private:
	vector<Token>& tokens;
	std::shared_ptr<vector<Node>> nodes;
	unsigned int tok_idx;
	Token* currentToken;
	//int parseCounter;
	//int binOpCounter;

	std::shared_ptr<Node> throwError(std::string details);

	std::shared_ptr<Node> bin_op(std::function<std::shared_ptr<Node>()>, tokenTypes op1, int op2 = NULL, std::function<std::shared_ptr<Node>()> func2 = NULL);
};

