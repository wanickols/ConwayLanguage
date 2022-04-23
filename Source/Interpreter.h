#pragma once

#include "Node.h"

class Number;

class Interpreter
{
public:

	Number visit(std::shared_ptr<Node> node);
	Number visit(NumberNode& numberNode);
	Number visit(UnaryOpNode& binOpNode);
	Number visit(BinOpNode& binOpNode);


	void no_visit_method(std::shared_ptr<Node> node);
};

