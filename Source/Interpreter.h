#pragma once

#include "Node.h"

class Number;
class Context;

class Interpreter
{
public:

	Interpreter(std::shared_ptr<Context> context);

	Number visit(std::shared_ptr<Node> node);
	Number visit(NumberNode& numberNode);
	Number visit(UnaryOpNode& binOpNode);
	Number visit(BinOpNode& binOpNode);


	void no_visit_method(std::shared_ptr<Node> node);

private:
	std::shared_ptr<Context> context;

};

