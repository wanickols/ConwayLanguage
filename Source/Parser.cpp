#include "pch.h"
#include "Parser.h"

//===============================
//========== Parser =============
//===============================

Parser::Parser(vector<Token>& tokens) : tokens(tokens), tok_idx(0), currentToken(nullptr)
{
	std::unique_ptr<vector<Node>> nodes = std::make_unique<vector<Node>>();
	advance();
}

void Parser::advance()
{

	if (tok_idx < tokens.size())
		currentToken = &tokens.at(tok_idx);

	++tok_idx;
}

std::shared_ptr<Node> Parser::parse()
{
	std::shared_ptr<Node> nodeP = expr();
	if (currentToken->getType() != tokenTypes::T_EOF) 
	{
		string details = "Expected *, or +, or -, or /";
		IllegalSyntaxError error(details, nodeP->getLinePosition());
		CW_CORE_ERROR(error.as_string());
	}

	return nodeP;

}

// : INT|FLOAT
// : (PLUS|MINUS) factor
// : LPAREN expr RPAREN
std::shared_ptr<Node> Parser::factor()
{

	const tokenTypes& type = currentToken->getType();

	//Unary Op
	if (type == tokenTypes::T_PLUS || type == tokenTypes::T_MINUS) 
	{
		Token* t = currentToken;
		advance();
		std::shared_ptr<Node> Fnode = factor();
		std::shared_ptr<UnaryOpNode> uNode = std::make_shared<UnaryOpNode>(*t, Fnode);
	
		return uNode;
	}
	//Parenthesis
	else if (type == T_LEFTPAR) 
	{
		advance();
		std::shared_ptr<Node> node = expr();
		//Close Parenthesis
		if (currentToken->getType() == T_RIGHTPAR)
		{
			advance();
			return node;
		}
		//Error
		else 
		{
			string details = "Expected a )";
			IllegalSyntaxError error(details, currentToken->getPosStart());
			CW_CORE_ERROR(error.as_string());
			std::shared_ptr<Node> node = std::make_shared<EmptyNode>(*currentToken);
			return node;
		}
	}
	//Binary Op
	else if (type == tokenTypes::T_INT || type == tokenTypes::T_FLOAT) {
		std::shared_ptr<Node> node = std::make_shared<NumberNode>(*currentToken);
		advance();
		return node;
	}
	//Error
	else { 
		
		string details = "Expected Int Or Float";
		IllegalSyntaxError error(details, currentToken->getPosStart());
		CW_CORE_ERROR(error.as_string());
		std::shared_ptr<Node> node = std::make_shared<EmptyNode>(*currentToken);
		return node;
	}
		
	
}

// : factor ((MUL|DIV) factor)*
std::shared_ptr<Node> Parser::term()
{
	return bin_op([this]() { return this->factor(); }, tokenTypes::T_MULTIPLY, tokenTypes::T_DIVIDE);
}

// : term ((PLUS | MINUS) term)*
std::shared_ptr<Node> Parser::expr()
{
	return bin_op([this]() { return this->term(); }, tokenTypes::T_PLUS, tokenTypes::T_MINUS);
}

// : func ((op1 | op2) func)*
std::shared_ptr<Node> Parser::bin_op(std::function<std::shared_ptr<Node>()> func, tokenTypes op1, tokenTypes op2)
{

	std::shared_ptr<Node> left = func();

	tokenTypes type = currentToken->getType();

	while (type == op1 || type == op2)
	{
		//Incrementing
		Token* op_tok = currentToken;
		advance();
		//setting right
		std::shared_ptr<Node> right = func();
		//recursively chaining left to make a tree
		std::shared_ptr<BinOpNode> newNodePtr = std::make_shared<BinOpNode>(left, *op_tok, right);

		left = newNodePtr;
		
		type = currentToken->getType();
	}

	//returns final left tree
	return left;

}

