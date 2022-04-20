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

	string parse();

	//Parser Definitions
	std::shared_ptr<Node> factor();
	std::shared_ptr<Node> term();
	std::shared_ptr<Node> expr();

private:
	vector<Token>& tokens;
	std::shared_ptr<vector<Node>> nodes;
	unsigned int tok_idx;
	Token* currentToken;

	std::shared_ptr<Node> bin_op(std::function<std::shared_ptr<Node>()>, tokenTypes op1, tokenTypes op2);
};

