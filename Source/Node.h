#pragma once

#include "Token.h"

const enum nodeTypes
{
	NT_NumberNode = 0,
	NT_BinOpNode,
	NT_UnaryOpNode,
	NT_EmptyNode
};

//Base Node
class Node
{
public:
	//Constructor
	Node(Token& tok, nodeTypes type);

	//Functions
	virtual string represent() { return "Error, base node called"; };

	//Accessors
	tokenTypes getTokenType() const;
	const nodeTypes getNodeType() const;

	const std::shared_ptr<LinePosition> getLinePosition() const;
protected:
	Token tok;
	nodeTypes type;
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

	EmptyNode(Token& tok) : Node(tok, nodeTypes::NT_EmptyNode) {};
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

class UnaryOpNode : public Node 
{
public:
	UnaryOpNode(Token& op_tok, std::shared_ptr<Node> other_node);

	string represent() override;

private:
	std::shared_ptr<Node> otherNode;
};

