#include "pch.h"
#include "Interpreter.h"
#include "Number.h"


Interpreter::Interpreter(std::shared_ptr<Context> context) : context(context)
{

}

Number Interpreter::visit(std::shared_ptr<Node> node)
{
	switch (node->getNodeType())
	{
	case(nodeTypes::NT_NumberNode):
		if (NumberNode* NNode = dynamic_cast<NumberNode*>(node.get()))
		{
			return visit(*NNode);
		}else
		{
			CW_CORE_ERROR("Number node type explcitly declared and wrong");
		}

		break;
	case(nodeTypes::NT_BinOpNode):
		if (BinOpNode* BNode = dynamic_cast<BinOpNode*>(node.get()))
		{
			return visit(*BNode);
		}
		else
		{
			CW_CORE_ERROR("Binary Operator node type explcitly declared and wrong");
		}
		break;
	case(nodeTypes::NT_UnaryOpNode):
		if (UnaryOpNode* UNode = dynamic_cast<UnaryOpNode*>(node.get()))
		{
			return visit(*UNode);
		}
		else
		{
			CW_CORE_ERROR("Unary Operator node type explcitly declared and wrong");
		}
		break;
	case(nodeTypes::NT_EmptyNode):
	default:
		no_visit_method(node);
		return Number(-1, node->getLinePosition(), context);
		break;
	}

	
}

Number Interpreter::visit(NumberNode& numberNode)
{

	
	if (numberNode.getTokenType() == tokenTypes::T_FLOAT) 
	{
		float val = numberNode.getToken().fvalue;

		//CW_CORE_TRACE("found number node {}", val);
		CW_CORE_WARN("There is no floats in this game! :D");
		return Number((int)val, numberNode.getLinePosition(),context);
	}
	else {
		int val = numberNode.getToken().value;
		Number num(val, numberNode.getLinePosition(), context);


		//CW_CORE_TRACE("found number node {}", val);
		return num;

	}

}

Number Interpreter::visit(UnaryOpNode& unOpNode)
{
	//CW_CORE_TRACE("found Unary operation node");
	Number other = visit(unOpNode.otherNode);


	if (unOpNode.getTokenType() == tokenTypes::T_MINUS) 
	{
		other.setValue(other.getValue() * -1);
	}
	return other;
}

Number Interpreter::visit(BinOpNode& binOpNode)
{
	//CW_CORE_TRACE("found binary operation node");
	Number left = visit(binOpNode.leftNode);
	Number right = visit(binOpNode.rightNode);

	Number result(0, binOpNode.getLinePosition(), context);
	switch (binOpNode.getTokenType()) 
	{
	case(tokenTypes::T_PLUS):
		result.setValue(left.added_to(right));
		break;
	case(tokenTypes::T_MINUS):
		result.setValue(left.subbed_by(right));
		break;
	case(tokenTypes::T_DIVIDE):
		result.setValue(left.dived_by(right));
		break;
	case(tokenTypes::T_MULTIPLY):
		result.setValue(left.multed_by(right));
		break;
	case(tokenTypes::T_POW):
		result.setValue(left.power_of(right));
		break;
	}

	return result;

}

void Interpreter::no_visit_method(std::shared_ptr<Node> node)
{
	CW_CORE_ERROR("No Visit Method Defined for " + node->represent());
}
