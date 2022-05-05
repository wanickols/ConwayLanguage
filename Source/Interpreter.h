#pragma once

#include "Node.h"

class Number;
class Context;

class Interpreter
{
public:

	//Constructor
	Interpreter(std::shared_ptr<Context> context);

	//Functions
	Number visit(std::shared_ptr<Node> node);

	

private:
	//variables
	std::shared_ptr<Context> context;

	//Visit Functions
	Number visit(NumberNode& numberNode);
	Number visit(UnaryOpNode& binOpNode);
	Number visit(BinOpNode& binOpNode);
	Number visit(VarAccessNode& binOpNode);
	Number visit(VarAssignNode& binOpNode);
	Number visit(IfNode& ifNode);

	//ErrorHandling
	void VarNotDefined(VarAccessNode& node);
	void no_visit_method(std::shared_ptr<Node> node);
};

