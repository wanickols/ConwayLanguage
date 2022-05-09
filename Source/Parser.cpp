#include "pch.h"
#include "Parser.h"
#include "Case.h"

//===============================
//========== Parser =============
//===============================

Parser::Parser(vector<Token>& tokens) : tokens(tokens), tok_idx(0), currentToken(nullptr)
{
	std::unique_ptr<vector<Node>> nodes = std::make_unique<vector<Node>>();
	BinKeywords = std::make_shared<unordered_set<string>>();
	BinKeywords->insert({ "AND", "OR" });
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
	if (currentToken->getType() != T_EOF) 
	{
		string details = "Expected *, or +, or -, or /";
		IllegalSyntaxError error(details, nodeP->getLinePosition());
		CW_CORE_ERROR(error.as_string());
	}

	return nodeP;

}

// : INT|FLOAT|IDENTIFIER 
// : LPAREN expr RPAREN
// : Keywords
std::shared_ptr<Node> Parser::atom()
{
	const tokenTypes& type = currentToken->getType();

	//Binary Op
	if (type == T_INT || type == T_FLOAT) {
		std::shared_ptr<Node> node = std::make_shared<NumberNode>(*currentToken);
		advance();
		return node;
	}
	else if (type == T_QUOTE) {
		advance();

		if (currentToken->getType() != T_IDENTIFIER) 
		{
			return throwError("Expected A String");
		}
		
		std::shared_ptr<StringNode> node = std::make_shared<StringNode>(*currentToken);
		advance();

		if (currentToken->getType() != T_QUOTE)
		{
			return throwError("Expected A Quote");
		}
		advance();

		return node;
	}
	else if (type == T_IDENTIFIER)
	{
		string varname = currentToken->svalue;
		std::shared_ptr<Node> node = std::make_shared<VarAccessNode>(*currentToken);
		advance();

		if (currentToken->getType() == T_EQ)
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
	//List
	else if (type == T_LEFTBRAK)
	{
		return list_expr();
	}
	//IF/For/While/Cell/Grid/MakeAlive 
	else if (type == T_KEYWORD)
	{
		string& keywordName =currentToken->svalue;
		if (keywordName == "IF")
			return if_expr();
		else if (keywordName == "FOR")
			return for_expr();
		else if (keywordName == "WHILE")
			return while_expr();
		else if (keywordName == "Grid" || keywordName == "Run" || keywordName == "Delay" || keywordName == "Clear" || keywordName == "Cell")
			return func_expr();
		else if (keywordName == "MakeAlive")
			return makeAlive_expr();
		else
			return throwError("Expected IF, FOR, WHILE");
	}
	//Error
	else {

		return throwError("Expected a '(', '+', '-', ',', '[', INT,FLOAT, KEYWORD, or IDENTIFIER");

	}
}


// : atom (POW factor)*
std::shared_ptr<Node> Parser::power()
{
	std::shared_ptr<std::unordered_set<tokenTypes>> types = std::make_shared<std::unordered_set<tokenTypes>>();
	types->insert( T_POW );
	return  bin_op([this]() { return this->atom(); }, types, [this]() { return this->factor(); });
}


// : (PLUS|MINUS) factor
// : power
std::shared_ptr<Node> Parser::factor()
{
	const tokenTypes& type = currentToken->getType();
	
	//Unary Op
	if (type == T_PLUS || type == T_MINUS)
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
	std::shared_ptr<std::unordered_set<tokenTypes>> types = std::make_shared<std::unordered_set<tokenTypes>>();
	types->insert({ T_MULTIPLY, T_DIVIDE });
	return bin_op([this]() { return this->factor(); }, types);
}

// : term ((PLUS | MINUS) term)*
std::shared_ptr<Node> Parser::arith_expr()
{
	std::shared_ptr<std::unordered_set<tokenTypes>> types = std::make_shared<std::unordered_set<tokenTypes>>();
	types->insert({ T_PLUS, T_MINUS });
	return bin_op([this]() { return this->term(); }, types);
}

// : Not cmpr_expr
// : arith_expr (EE|LT|GT|LTE|GTE arith_expr)
std::shared_ptr<Node> Parser::cmpr_expr()
{
	tokenTypes type = currentToken->getType();

	//Not handling
	if (type == T_KEYWORD)
	{
		string symbolName = currentToken->svalue;
		if (symbolName == "NOT")
		{
			return returnNotExpr();
		}
	}
	else if (type == T_NOT)
	{
		std::shared_ptr<Node> Cnode = cmpr_expr();
		std::shared_ptr<UnaryOpNode> uNode = std::make_shared<UnaryOpNode>(*currentToken, Cnode);
		return uNode;
	}

	//arithmExpr
	std::shared_ptr<std::unordered_set<tokenTypes>> types = std::make_shared<std::unordered_set<tokenTypes>>();
	types->insert({ T_EE, T_LT, T_GT, T_LTE, T_GTE });
	return bin_op([this]() { return this->arith_expr(); }, types);
}

std::shared_ptr<Node> Parser::returnNotExpr()
{
	std::shared_ptr<Node> Cnode = cmpr_expr();
	std::shared_ptr<UnaryOpNode> uNode = std::make_shared<UnaryOpNode>(*currentToken, Cnode);
	return uNode;
}


// : KEYWORD(VARIABLETYPE) IDENTIFIER EQUALS expr
// : cmpr_expr ((KEYWORD(AND|OR_)) cmpr_expr)
std::shared_ptr<Node> Parser::expr()
{
	//Keyword assigning
	if (currentToken->getType() == T_KEYWORD)
	{
		string symbolName = currentToken->svalue;
		if (symbolName == "Int") {

			advance();

			if (currentToken->getType() == T_IDENTIFIER)
			{
				string varname = currentToken->svalue;
				advance();
				if (currentToken->getType() == T_EQ) {
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
		else if (symbolName == "NOT")
		{
			return cmpr_expr();
		}
	}

	return bin_op_key([this]() { return this->cmpr_expr(); }, BinKeywords);

}
//LEFTBRAK (expr COMMA expr RIGHTBRAK
std::shared_ptr<Node> Parser::list_expr()
{
	std::shared_ptr<vector<std::shared_ptr<Node>>> elementNodes = std::make_shared<vector<std::shared_ptr<Node>>>();
	Token& tok = *currentToken;

	advance();

	string varname = "";
	if (currentToken->getType() == T_RIGHTBRAK)
	{
		advance();

		if (currentToken->getType() == T_IDENTIFIER)
		{
			varname = currentToken->svalue;
			advance();
		}

		return std::make_shared<ListNode>(*currentToken, varname, elementNodes);
	}
	else
	{
		elementNodes->push_back(expr());

		while (currentToken->getType() == T_COMMA)
		{
			advance();


			elementNodes->push_back(expr());

		
		}

	}


	if (currentToken->getType() != T_RIGHTBRAK)
	{
		return throwError("Expected ] or '(', ',', '[', INT,FLOAT, KEYWORD, IDENTIFIER");
	}

	advance();

	
	if (currentToken->getType() == T_IDENTIFIER)
	{
		varname = currentToken->svalue;
		advance();
	}

	return std::make_shared<ListNode>(*currentToken, varname, elementNodes);
}


// KEYWORD ident? LEFT PAR expr COMMA? expr?... RIGHT PAR
std::shared_ptr<Node> Parser::func_expr()
{
	Token& tok = *currentToken;

	string varType = currentToken->svalue;

	advance();

	string varname = "";
	if (currentToken->getType() == T_IDENTIFIER)
	{
		varname = currentToken->svalue;
		advance();
	}


	if (currentToken->getType() != T_LEFTPAR)
	{
		return throwError("Expected a (");
	}

	advance();

	std::shared_ptr<vector<shared_ptr<Node>>> arguments = std::make_shared<vector<shared_ptr<Node>>>();

	//No Paremeters
	if (currentToken->getType() == T_RIGHTPAR)
	{
		advance();
		return std::make_shared<FuncNode>(tok, arguments, varname, varType);
	}

	arguments->push_back(expr());


	//After One Paramter
	if (currentToken->getType() == T_RIGHTPAR)
	{
		advance();
		return std::make_shared<FuncNode>(tok, arguments, varname, varType);
	}
	else
	{

		//Endless Parameters
		while(currentToken->getType() == T_COMMA)
		{
			advance();

			arguments->push_back(expr());

		}

	}

	//Closing Par
	if (currentToken->getType() != T_RIGHTPAR)
	{
		return throwError("Expected a )");
	}

	advance();

	//Node
	return std::make_shared<FuncNode>(tok, arguments, varname, varType);
}

// KEYWORD:MakeAlive LEFT PAR list_expr RIGHT PAR
std::shared_ptr<Node> Parser::makeAlive_expr()
{
	Token& tok = *currentToken;

	if (currentToken->svalue != "MakeAlive")
	{
		return throwError("Expected MakeAlive keyword");
	}

	advance();

	if (currentToken->getType() != T_LEFTPAR)
	{
		return throwError("Expected a (");
	}

	advance();

	if (currentToken->getType() != T_IDENTIFIER)
	{
		return throwError("Expected Grid Name");
	}
	string gridName = currentToken->svalue;
	advance();


	if (currentToken->getType() != T_COMMA)
	{
		return throwError("Expected a ,");
	}

	advance();

	std::shared_ptr<Node> table = list_expr();


	if (currentToken->getType() != T_RIGHTPAR)
	{
		return throwError("Expected a )");
	}

	advance();

	return std::make_shared<MakeAlive>(tok, gridName, table);
}






// KEYWORD:IF expr KEYWORD:THEN expr 
// KEYWORD:ELIF expr THEN expr
// KEYWORD:ELSE expr
std::shared_ptr<Node> Parser::if_expr()
{
	Token& tok = *currentToken;

	if(currentToken->svalue != "IF")
	{
		return throwError("Expected IF keyword");
	}

	advance();

	std::shared_ptr<Node> cond = expr();

	if (currentToken->svalue != "THEN")
	{
		return throwError("Expected THEN keyword");
	}

	advance();

	std::shared_ptr<Node> express = expr();
		
	Case case_(cond, express);
	
	std::shared_ptr<vector<Case>> cases = std::make_shared<vector<Case>>();
	cases->push_back(case_);

	while (currentToken->svalue == "ELIF") 
	{
		advance();
		std::shared_ptr<Node> condition = expr();

		if (currentToken->svalue != "THEN")
		{
			return throwError("Expected THEN keyword");
		}

		advance();
		std::shared_ptr<Node> expression = expr();

		Case next_case(condition, expression);

		cases->push_back(next_case);
	}

	std::shared_ptr<Node> node;

	if (currentToken->svalue == "ELSE") 
	{
		advance();
		node = expr();
	}



	return std::make_shared<IfNode>(tok, cases, node);
}

std::shared_ptr<Node> Parser::for_expr()
{
	Token& tok = *currentToken;

	if (currentToken->svalue != "FOR")
	{
		return throwError("Expected FOR keyword");
	}

	advance();

	if (currentToken->getType() != T_IDENTIFIER)
	{
		return throwError("Expected Identifier");
	}

	string varName = currentToken->svalue;
	advance();

	if (currentToken->getType() != T_EQ)
	{
		return throwError("Expected Equals");
	}

	advance();

	std::shared_ptr<Node> start_value = expr();

	if (currentToken->svalue != "TO")
	{
		return throwError("Expected TO keyword");
	}

	advance();
	std::shared_ptr<Node> end_value = expr();

	std::shared_ptr<Node> step_value = nullptr;
	if (currentToken->svalue == "STEP")
	{
		advance();
		step_value = expr();
	}

	if (currentToken->svalue != "THEN")
	{
		return throwError("Expected THEN keyword");
	}
	
	advance();
	std::shared_ptr<Node> body = expr();

	return(std::make_shared<ForNode>(tok, varName, "Int", start_value, end_value, step_value, body));

}

std::shared_ptr<Node> Parser::while_expr()
{
	Token& tok = *currentToken;

	if (currentToken->svalue != "WHILE")
	{
		return throwError("Expected IF keyword");
	}

	advance();
	std::shared_ptr<Node> cond = expr();


	if (currentToken->svalue != "THEN")
	{
		return throwError("Expected THEN keyword");
	}

	advance();
	std::shared_ptr<Node> express = expr();

	return std::make_shared<WhileNode>(tok, std::make_shared<Case>(cond, express));
}
	



std::shared_ptr<Node> Parser::throwError(std::string details)
{
	IllegalSyntaxError error(details, currentToken->getPosStart());
	CW_CORE_ERROR(error.as_string());
	std::shared_ptr<Node> node = std::make_shared<EmptyNode>(*currentToken);
	return node;
}

// : func ((op1 | op2) func)*
std::shared_ptr<Node> Parser::bin_op(std::function<std::shared_ptr<Node>()> func_a, std::shared_ptr<unordered_set<tokenTypes>> ops, std::function<std::shared_ptr<Node>()> func_b)
{
	if (func_b == NULL)
		func_b = func_a;


	std::shared_ptr<Node> left = func_a();

	tokenTypes type = currentToken->getType();
		while (ops->find(type) != ops->end())
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

std::shared_ptr<Node> Parser::bin_op_key(std::function<std::shared_ptr<Node>()> func_a, std::shared_ptr<unordered_set<string>> ops, std::function<std::shared_ptr<Node>()> func_b)
{
	if (func_b == NULL)
		func_b = func_a;


	std::shared_ptr<Node> left = func_a();

	if (currentToken->getType() == T_KEYWORD)
	{
		string symbolName = currentToken->svalue;
		while (ops->find(symbolName) != ops->end())
		{
			//Incrementing
			Token* op_tok = currentToken;
			advance();
			//setting right
			std::shared_ptr<Node> right = func_b();
			//recursively chaining left to make a tree
			std::shared_ptr<BinOpNode> newNodePtr = std::make_shared<BinOpNode>(left, *op_tok, right);

			left = newNodePtr;

			symbolName = currentToken->svalue;
		}
	}


	//returns final left tree
	return left;
}
