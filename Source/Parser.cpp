#include "pch.h"
#include "Parser.h"

//===============================
//========== Parser =============
//===============================

Parser::Parser(vector<Token>& tokens) : tokens(tokens), tok_idx(0), currentToken(nullptr)
{
	std::unique_ptr<vector<Node>> nodes = std::make_unique<vector<Node>>();
	
}

void Parser::advance()
{

	if (tok_idx < tokens.size())
		currentToken = &tokens.at(tok_idx);

	++tok_idx;
}

std::shared_ptr<Node> Parser::parse()
{
	advance();
	std::shared_ptr<Node> nodeP = expr();
	if (currentToken->getType() != tokenTypes::T_EOF) 
	{
		string details = "Expected *, or +, or -, or /";
		IllegalSyntaxError error(details, nodeP->getLinePosition());
		CW_CORE_ERROR(error.as_string());
	}

	return nodeP;

}

// : INT|FLOAT|IDENTIFIER 
// : LPAREN expr RPAREN
std::shared_ptr<Node> Parser::atom()
{
	const tokenTypes& type = currentToken->getType();

	//Binary Op
	if (type == tokenTypes::T_INT || type == tokenTypes::T_FLOAT) {
		std::shared_ptr<Node> node = std::make_shared<NumberNode>(*currentToken);
		advance();
		return node;
	}
	else if (type == tokenTypes::T_IDENTIFIER) 
	{
		string varname = currentToken->svalue;
		std::shared_ptr<Node> node = std::make_shared<VarAccessNode>(*currentToken);
		advance();

		if (currentToken->getType() == tokenTypes::T_EQUALS)
		{
			advance();
			string symbolName = "EXISTS";
			std::shared_ptr<VarAssignNode> VarNode = std::make_shared<VarAssignNode>(*currentToken, varname, expr(), symbolName);
			return VarNode;
		}

		return node;
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
			return throwError("Expected a )");
		}
	}
	//Error
	else {

		return throwError("Expected a '(', '+', '-', INT,FLOAT, or IDENTIFIER");

	}
}


// : atom (POW factor)*
std::shared_ptr<Node> Parser::power()
{
	//Two pows redudant, but can't pass in null or -1 without unforseen consequences. 
	return  bin_op([this]() { return this->atom(); }, tokenTypes::T_POW, tokenTypes::T_POW, [this]() { return this->factor(); });
}


// : (PLUS|MINUS) factor
// : power
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
	else 
	{
		//The reason we can do this is because power calls atom by defualt. If it has a POW it will also do that, if not it atom will be return instead untouched and this will cover it
		return power();
	}
		
	
}

// : factor ((MUL|DIV) factor)*
std::shared_ptr<Node> Parser::term()
{
	return bin_op([this]() { return this->factor(); }, tokenTypes::T_MULTIPLY, tokenTypes::T_DIVIDE);
}

// : KEYWORD IDENTIFIER EQUALS expr
// : term ((PLUS | MINUS) term)*
std::shared_ptr<Node> Parser::expr()
{
	//Keyword assigning
	if (currentToken->getType() == tokenTypes::T_KEYWORD)
	{
		string symbolName = currentToken->svalue;
		if (symbolName == "Int") {

			advance();

			if (currentToken->getType() == T_IDENTIFIER)
			{
				string varname = currentToken->svalue;
				advance();
				if (currentToken->getType() == T_EQUALS) {
					advance();
					std::shared_ptr<VarAssignNode> VarNode = std::make_shared<VarAssignNode>(*currentToken, varname, expr(), symbolName);
					return VarNode;
				}
				else
				{
					return throwError("Expected an =");
				}

			}
			else
			{
				return throwError("Expected an IDENTIFIER");
			}
		}
		else
		{
			return throwError("Undefined Keyword");
		}
	}

	return bin_op([this]() { return this->term(); }, tokenTypes::T_PLUS, tokenTypes::T_MINUS);
}


std::shared_ptr<Node> Parser::throwError(std::string details)
{
	IllegalSyntaxError error(details, currentToken->getPosStart());
	CW_CORE_ERROR(error.as_string());
	std::shared_ptr<Node> node = std::make_shared<EmptyNode>(*currentToken);
	return node;
}

// : func ((op1 | op2) func)*
std::shared_ptr<Node> Parser::bin_op(std::function<std::shared_ptr<Node>()> func_a, tokenTypes op1, int op2, std::function<std::shared_ptr<Node>()> func_b)
{
	if (func_b == NULL)
		func_b = func_a;


	std::shared_ptr<Node> left = func_a();

	tokenTypes type = currentToken->getType();
		while (type == op1 || type == op2)
		{
			//Incrementing
			Token* op_tok = currentToken;
			advance();
			//setting right
			std::shared_ptr<Node> right = func_b();
			//recursively chaining left to make a tree
			std::shared_ptr<BinOpNode> newNodePtr = std::make_shared<BinOpNode>(left, *op_tok, right);

			left = newNodePtr;

			type = currentToken->getType();
		}
	

	//returns final left tree
	return left;

}