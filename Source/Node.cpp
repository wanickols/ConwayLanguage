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
NumberNode::NumberNode(Token& tok) : Node(tok, nodeTypes::NT_NumberNode)
{
}

string NumberNode::represent()
{
	return tok.Representation();
}


//=======BinOp Node==========
BinOpNode::BinOpNode(std::shared_ptr<Node> left_node, Token& op_tok, std::shared_ptr<Node> right_node) : Node(op_tok, nodeTypes::NT_BinOpNode), leftNode(left_node), rightNode(right_node)
{
}

string BinOpNode::represent()
{
	stringstream ss;
	ss << '(' << leftNode->represent() << ", " << tok.Representation() << ", " << rightNode->represent() << ")";
	return ss.str();
}

UnaryOpNode::UnaryOpNode(Token& op_tok, std::shared_ptr<Node> other_node) : Node(op_tok, nodeTypes::NT_UnaryOpNode), otherNode(other_node)
{
}

string UnaryOpNode::represent()
{
	stringstream ss;
	ss << tok.Representation() << " " << otherNode->represent();
	return ss.str();
}
