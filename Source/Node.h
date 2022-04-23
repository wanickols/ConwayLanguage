#pragma once

#include "Token.h"

//Base Node
class Node
{
public:
	//Constructor
	Node(Token& tok);

	//Functions
	virtual string represent() { return "Error, base node called"; };

	//Accessors
	tokenTypes getTokenType() const;

	const std::shared_ptr<LinePosition> getLinePosition() const;
protected:
	Token tok;
};

//Node Implementations
class NumberNode : public Node
{
public:
	NumberNode(Token& tok);

	string represent() override;
};

//This is not a great plan but it is what I could get to work
//This class is an emtpy node that is used to satisfy functions that must return a node,
//but the if statement is more for error checking then anything else. 
class EmptyNode : public Node
{
public:

	EmptyNode(Token& tok) : Node(tok) {};
	string represent() override { return ""; };
};

class BinOpNode : public Node 
{
public:
	BinOpNode(std::shared_ptr<Node> left_node, Token& op_tok, std::shared_ptr<Node> right_node);

	string represent() override;
private:
	std::shared_ptr<Node> leftNode;
	std::shared_ptr<Node> rightNode;
};

