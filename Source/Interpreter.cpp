#include "pch.h"
#include "Interpreter.h"
#include "Number.h"
#include "Context.h"
#include "SymbolTable.h"
#include "Case.h"

Interpreter::Interpreter(std::shared_ptr<Context> context) : context(context), maxWhileSize(10000)
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
			return no_visit_method(node);
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
			return no_visit_method(node);
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
			return no_visit_method(node);
		}
		break;
	case(nodeTypes::NT_VarAccessNode):
		if (VarAccessNode* VarAccessNd = dynamic_cast<VarAccessNode*>(node.get()))
		{
			return visit(*VarAccessNd);
		}
		else
		{
			CW_CORE_ERROR("Variable Acess node type explcitly declared and wrong");
			return no_visit_method(node);
		}
		break;
	case(nodeTypes::NT_VarAssignNode):
		if (VarAssignNode* VarAssignNd = dynamic_cast<VarAssignNode*>(node.get()))
		{
			return visit(*VarAssignNd);
		}
		else
		{
			CW_CORE_ERROR("Variable Assign node type explcitly declared and wrong");
			return no_visit_method(node);
		}
		break;
	case(nodeTypes::NT_IfNode):
			if (IfNode* ifNd = dynamic_cast<IfNode*>(node.get()))
			{
				return visit(*ifNd);
			}
			else
			{
				CW_CORE_ERROR("Variable If node type explcitly declared and wrong");
				return no_visit_method(node);
			}
		break;
	case(nodeTypes::NT_ForNode):
		if (ForNode* forNode = dynamic_cast<ForNode*>(node.get()))
		{
			return visit(*forNode);
		}
		else
		{
			CW_CORE_ERROR("Variable For node type explcitly declared and wrong");
			return no_visit_method(node);
		}
		break;
	case(nodeTypes::NT_WhileNode):
		if (WhileNode* whileNode = dynamic_cast<WhileNode*>(node.get()))
		{
			return visit(*whileNode);
		}
		else
		{
			CW_CORE_ERROR("Variable While node type explcitly declared and wrong");
			return no_visit_method(node);
		}
		break;
	case(nodeTypes::NT_EmptyNode):
	default:
		return no_visit_method(node);
		break;
	}
	
	
}

void Interpreter::setMaxWhileSize(const int size)
{
	maxWhileSize = size;
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

	tokenTypes type = unOpNode.getTokenType();
	if (type == tokenTypes::T_MINUS)
	{
		other.setValue(other.getValue() * -1);
	}
	else if (type == tokenTypes::T_NOT) 
	{
	
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
	case(tokenTypes::T_EE):
		result.setValue(left.getComparison_EE(right));
		break;
	case(tokenTypes::T_NE):
		result.setValue(left.getComparison_NE(right));
		break;
	case(tokenTypes::T_LT):
		result.setValue(left.getComparison_LT(right));
		break;
	case(tokenTypes::T_GT):
		result.setValue(left.getComparison_GT(right));
		break;
	case(tokenTypes::T_LTE):
		result.setValue(left.getComparison_LTE(right));
		break;
	case(tokenTypes::T_GTE):
		result.setValue(left.getComparison_GTE(right));
		break;
	case(tokenTypes::T_KEYWORD):
		result.setValue(left.getComparison_KEYWORD(right, binOpNode.getToken().svalue));
		break;
	}

	return result;

}

Number Interpreter::visit(VarAccessNode& accessNode)
{
	string var_name = accessNode.getToken().svalue;
	Number result(0, accessNode.getLinePosition(), context);

	std::shared_ptr<std::pair<string, std::any>> pair_val = context->symbolTable->get(var_name);

	string type_name = context->symbolTable->get(var_name)->first;
	 
	if (type_name == "Int") 
	{
		result.setValue(std::any_cast<int>(pair_val->second));
	}
	else if (type_name == "Float") 
	{
		float f = std::any_cast<float>(pair_val->second);
		CW_CORE_WARN("There is no floats in this game! :D");
		int i = (int)f;
		result.setValue(i);
	}
	else 
	{
		if (type_name == "null")
			VarNotDefined(accessNode);
		else {
			CW_CORE_ERROR("Invalid Type Name");
		}
	}

	
	return result;
}

Number Interpreter::visit(VarAssignNode& assignNode)
{
	Number result(0, assignNode.getLinePosition(), context);
	Number adder = visit(assignNode.valueNode);
	int val = adder.getValue();
	if(assignNode.varType != "Exist")
		context->symbolTable->set(assignNode.varName, val, assignNode.varType);
	else 
	{
		context->symbolTable->set(assignNode.varName, val);
	}
	result.setValue(val);
	return result;
}

Number Interpreter::visit(IfNode& ifNode)
{
	
	for (int i = 0; i < ifNode.cases->size(); i++) 
	{
		Number cond = visit(ifNode.cases->at(i).condition);
		if (cond.getValue())
			return visit(ifNode.cases->at(i).expression);
	}
	if (ifNode.elseNode != nullptr)
		return visit(ifNode.elseNode);
	else
	{
		return Number();
	}
}

Number Interpreter::visit(ForNode& forNode)
{
	Number startValue = visit(forNode.startNode);
	Number endValue = visit(forNode.endNode);

	Number stepValue;
	int step = 1;
	if (forNode.stepNode != nullptr) 
	{
		stepValue = visit(forNode.stepNode);
		step = stepValue.getValue();
	}

	
	int i = startValue.getValue();
	int end = endValue.getValue();
	if (step > 0) 
	{
		while (i < end) {
			context->symbolTable->set(forNode.varName, i, forNode.varType);
			
			visit(forNode.expression);

			i += step;
		}
	}
	else if (step < 0) 
	{
		while (i > end) {
			context->symbolTable->set(forNode.varName, i, forNode.varType);

			visit(forNode.expression);
			
			i += step;
		}
	}
	else 
	{
		return throwError("Step Value Was Invalid");
	}
	return Number();
}

Number Interpreter::visit(WhileNode& whileNode)
{
	int counter = 0;


	while(true)
	{
		Number cond = visit(whileNode.case_->condition);
		if (!cond.getValue())
			break;
		
		visit(whileNode.case_->expression);

		if (counter > maxWhileSize)
			break;
	
	}

	return Number();
}

Number Interpreter::VarNotDefined(VarAccessNode& node)
{
	string details = "Variable {} is Not defined";
	RTError error(details, node.getLinePosition(), context);
	CW_CORE_ERROR(error.as_string(), node.getToken().svalue);
	return Number();
}

Number Interpreter::no_visit_method(std::shared_ptr<Node> node)
{
	CW_CORE_ERROR("No Visit Method Defined for " + node->represent());
	return Number(-1, node->getLinePosition(), context);
}

Number Interpreter::throwError(std::string details)
{
	CW_CORE_ERROR(details);
	return Number();
}
