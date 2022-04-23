#include "pch.h"
#include "Node.h"


//=======Base Node==========
Node::Node(Token& tok) : tok(tok)
{

}

tokenTypes Node::getTokenType() const
{

	return this->tok.getType();
}

const std::shared_ptr<LinePosition> Node::getLinePosition() const
{
	return tok.getPosStart();
}


//=======Number Node==========
NumberNode::NumberNode(Token& tok) : Node(tok)
{
}

string NumberNode::represent()
{
	return tok.Representation();
}


//=======BinOp Node==========
BinOpNode::BinOpNode(std::shared_ptr<Node> left_node, Token& op_tok, std::shared_ptr<Node> right_node) : Node(op_tok), leftNode(left_node), rightNode(right_node)
{
}

string BinOpNode::represent()
{
	stringstream ss;
	ss << '(' << leftNode->represent() << ", " << tok.Representation() << ", " << rightNode->represent() << ")";
	return ss.str();
}
