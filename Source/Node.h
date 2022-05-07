#pragma once

#include "Token.h"

class Case;

const enum nodeTypes
{
	NT_NumberNode = 0,
	NT_BinOpNode,
	NT_UnaryOpNode,
	NT_VarAssignNode,
	NT_VarAccessNode,
	NT_IfNode,
	NT_ForNode,
	NT_WhileNode,
	NT_ListNode,
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
	const Token& getToken() const;

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

	std::shared_ptr<Node> leftNode;
	std::shared_ptr<Node> rightNode;
};

class UnaryOpNode : public Node 
{
public:
	UnaryOpNode(Token& op_tok, std::shared_ptr<Node> other_node);

	string represent() override;

	std::shared_ptr<Node> otherNode;
};

class VarAssignNode : public Node 
{
public:
	VarAssignNode(Token& op_tok, string var_name, std::shared_ptr<Node> other_node, string var_type);

	string represent() override;

	string varName;
	string varType;
	std::shared_ptr<Node> valueNode;

};

class VarAccessNode : public Node
{
public:
	VarAccessNode(Token& op_tok);
	string represent() override;
};

class IfNode : public Node
{
public:
	IfNode(Token& op_tok, std::shared_ptr<vector<Case>> cases, std::shared_ptr<Node> else_node);
	string represent() override;

	std::shared_ptr<vector<Case>> cases;
	std::shared_ptr<Node> elseNode;
};

class ForNode : public Node
{
public:
	ForNode(Token& op_tok, string var_name, string var_type, std::shared_ptr<Node> start_node, std::shared_ptr<Node> end_node, std::shared_ptr<Node> step_node, std::shared_ptr<Node> expression);
	string represent() override;

	string varName;
	string varType;
	std::shared_ptr<Node> startNode;
	std::shared_ptr<Node> endNode;
	std::shared_ptr<Node> stepNode;  
	std::shared_ptr<Node> expression;
};

class WhileNode : public Node
{
public:
	WhileNode(Token& op_tok, std::shared_ptr<Case> passed_case);
	string represent() override;

	std::shared_ptr<Case> case_;
};

class ListNode : public Node
{
public:
	ListNode(Token& op_tok, std::shared_ptr<std::vector<std::shared_ptr<Node>>> element_nodes);
	string represent() override;

	std::shared_ptr<std::vector<std::shared_ptr<Node>>> elementNodes;
};