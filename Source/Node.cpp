#include "pch.h"
#include "Node.h"


//=======Base Node==========
Node::Node(Token& tok, nodeTypes type) : tok(tok), type(type)
{

}

tokenTypes Node::getTokenType() const
{

	return this->tok.getType();
}

const nodeTypes Node::getNodeType() const
{
	return type;
}

const Token& Node::getToken() const
{
	return tok;
}

const std::shared_ptr<LinePosition> Node::getLinePosition() const
{
	return tok.getPosStart();
}


//=======Number Node==========
NumberNode::NumberNode(Token& tok) : Node(tok, NT_NumberNode)
{
}

string NumberNode::represent()
{
	return tok.Representation();
}


//=======BinOp Node==========
BinOpNode::BinOpNode(std::shared_ptr<Node> left_node, Token& op_tok, std::shared_ptr<Node> right_node) : Node(op_tok, NT_BinOpNode), leftNode(left_node), rightNode(right_node)
{
}

string BinOpNode::represent()
{
	stringstream ss;
	ss << '(' << leftNode->represent() << ", " << tok.Representation() << ", " << rightNode->represent() << ")";
	return ss.str();
}

UnaryOpNode::UnaryOpNode(Token& op_tok, std::shared_ptr<Node> other_node) : Node(op_tok, NT_UnaryOpNode), otherNode(other_node)
{
}

string UnaryOpNode::represent()
{
	stringstream ss;
	ss << tok.Representation() << " " << otherNode->represent();
	return ss.str();
}

VarAssignNode::VarAssignNode(Token& op_tok, string var_name, std::shared_ptr<Node> other_node, string var_type) : Node(op_tok, NT_VarAssignNode), varName(var_name), valueNode(other_node), varType(var_type)
{
}


string VarAssignNode::represent()
{
	stringstream ss;
	ss << varName << " = " << valueNode->represent();
	return ss.str();
}

VarAccessNode::VarAccessNode(Token& op_tok) : Node(op_tok, NT_VarAccessNode)
{
}

string VarAccessNode::represent()
{
	stringstream ss;
	ss << tok.Representation();
	return ss.str();
}

IfNode::IfNode(Token& op_tok, std::shared_ptr<vector<Case>> cases, std::shared_ptr<Node> else_node) : Node(op_tok, NT_IfNode), cases(cases), elseNode(else_node)
{

}

string IfNode::represent()
{
	stringstream ss;
	ss << tok.Representation();
	return ss.str();
}

ForNode::ForNode(Token& tok, string var_name, string var_type, std::shared_ptr<Node> start_node, std::shared_ptr<Node> end_node, std::shared_ptr<Node> step_node, std::shared_ptr<Node> expression) : Node(tok, NT_ForNode), startNode(start_node), endNode(end_node), stepNode(step_node), expression(expression), varName(var_name), varType(var_type)
{
}

string ForNode::represent()
{
	//Add Representation
	stringstream ss;
	ss << tok.Representation();
	return ss.str();
}

WhileNode::WhileNode(Token& op_tok, std::shared_ptr<Case> passed_case) : Node(op_tok, NT_WhileNode), case_(passed_case)
{
}

string WhileNode::represent()
{
	//Add Representation
	stringstream ss;
	ss << tok.Representation();
	return ss.str();
}

ListNode::ListNode(Token& tok, std::shared_ptr<std::vector<std::shared_ptr<Node>>> element_nodes) : Node(tok , NT_ListNode), elementNodes(element_nodes)
{
}

string ListNode::represent()
{
	stringstream ss;
	ss << tok.Representation();

	for (int i = 0; i < elementNodes->size(); i++)
		ss << elementNodes->at(i)->represent() << ", ";

	return ss.str();
}

CellNode::CellNode(Token& tok, std::shared_ptr<Node> isAliveBool) : Node(tok, NT_CellNode), isAlive(isAliveBool)
{
}

string CellNode::represent()
{
	stringstream ss;
	ss << tok.Representation() << '(' << isAlive->represent() << ')';
	return ss.str();
}

MakeAlive::MakeAlive(Token& tok, string gridname, std::shared_ptr<Node> aliveTable) : Node(tok, NT_AliveNode), aliveTable(aliveTable), gridName(gridname)
{
}

string MakeAlive::represent()
{
	stringstream ss;
	ss << tok.Representation() << '(' << aliveTable->represent() << ')';
	return ss.str();
}

FuncNode::FuncNode(Token& tok, std::shared_ptr<vector<shared_ptr<Node>>> arguments, string varname, string vartype) : Node(tok, NT_FuncNode), arguments(arguments), varName(varname), varType(vartype)
{

}

string FuncNode::represent()
{
	stringstream ss;
	ss << tok.Representation();
	ss << '(';
	for (int i = 0; i < arguments->size() -1; i++)
		ss << arguments->at(i)->represent() << ", ";

	ss << arguments->back()->represent() << ')';
	return ss.str();
}
