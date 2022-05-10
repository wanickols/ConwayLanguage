#include "pch.h"
#include "Interpreter.h"
#include "Number.h"
#include "Context.h"
#include "SymbolTable.h"
#include "Case.h"
#include "List.h"
#include "Cell.h"
#include "Grid.h"


Interpreter::Interpreter(std::shared_ptr<Context> context) : context(context), maxWhileSize(10000)
{

}

Number Interpreter::visit(std::shared_ptr<Node> node)
{
	switch (node->getNodeType())
	{
	case(NT_NumberNode):
		if (NumberNode* NNode = dynamic_cast<NumberNode*>(node.get()))
		{
			return visit(*NNode);
		}else
		{
			CW_CORE_ERROR("Number node type explcitly declared and wrong");
			return no_visit_method(node);
		}

		break;
	case(NT_StringNode):
		if (StringNode* sNode = dynamic_cast<StringNode*>(node.get()))
		{
			return visit(*sNode);
		}
		else
		{
			CW_CORE_ERROR("Number node type explcitly declared and wrong");
			return no_visit_method(node);
		}

		break;
	case(NT_BinOpNode):
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
	case(NT_UnaryOpNode):
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
	case(NT_VarAccessNode):
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
	case(NT_VarAssignNode):
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
	case(NT_ListNode):
		if (ListNode* ifNd = dynamic_cast<ListNode*>(node.get()))
		{
			return visit(*ifNd);
		}
		else
		{
			CW_CORE_ERROR("Variable List node type explcitly declared and wrong");
			return no_visit_method(node);
		}
		break;
	case(NT_IfNode):
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
	case(NT_ForNode):
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
	case(NT_WhileNode):
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
	case(NT_FuncNode):
		if (FuncNode* funcNode = dynamic_cast<FuncNode*>(node.get()))
		{
			return visit(*funcNode);
		}
		else
		{
			CW_CORE_ERROR("Grid node type explcitly declared and wrong");
			return no_visit_method(node);
		}
		break;
	case(NT_AliveNode):
		if (MakeAlive* aliveNode = dynamic_cast<MakeAlive*>(node.get()))
		{
			return visit(*aliveNode);
		}
		else
		{
			CW_CORE_ERROR("Alive node type explcitly declared and wrong");
			return no_visit_method(node);
		}
		break;
	case(NT_EmptyNode):
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
		return Number(val, numberNode.getLinePosition(), context);

	}

}

Number Interpreter::visit(StringNode& numberNode)
{
	string val = numberNode.getToken().svalue;
	return Number(val, numberNode.getLinePosition(), context);
}

Number Interpreter::visit(UnaryOpNode& unOpNode)
{
	//CW_CORE_TRACE("found Unary operation node");
	Number other = visit(unOpNode.otherNode);

	tokenTypes type = unOpNode.getTokenType();
	if (type == tokenTypes::T_MINUS)
	{
		int thisVal = 0;

		if (!other.getInt(thisVal))
		{
			return throwError("No - Operator exist for Type given");
		}

		other.setValue(thisVal * -1);
	}
	else if (type == tokenTypes::T_NOT) 
	{
		other.notted();
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
	else if (type_name == "Grid") 
	{
		result.setValue(std::any_cast<std::shared_ptr<Grid>>(pair_val->second));
	}
	else if (type_name == "List")
	{
		result.setValue(std::any_cast<std::shared_ptr<List>>(pair_val->second));
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
	
	std::shared_ptr<Grid> val;
	
	if(!adder.getGrid(val))
	{

		
		//int
		int val1 = 0;

		if (!adder.getInt(val1)) {
			return throwError("Invalid Type for Adder");
		}
	
	
		if (assignNode.varType != "Exist")
			context->symbolTable->set(assignNode.varName, val1, assignNode.varType);
		else
		{
			context->symbolTable->set(assignNode.varName, val1);
		}
		result.setValue(val1);
		return result;
	}


	if(assignNode.varType != "Exist")
		context->symbolTable->set(assignNode.varName, val, assignNode.varType);
	else 
	{
		context->symbolTable->set(assignNode.varName, val);
	}
	result.setValue(val);
	return result;
}

Number Interpreter::visit(ListNode& listNode)
{
	
 
	std::shared_ptr<vector<Number>> nums = std::make_shared<vector<Number>>();

	for (int i = 0; i < listNode.elementNodes->size(); i++) 
	{

		nums->push_back(this->visit(listNode.elementNodes->at(i)));
	}



	std::shared_ptr<List> list = std::make_shared<List>(nums);


	//Set grid in context
	if (listNode.varName != "")
		context->symbolTable->set(listNode.varName, list, "List");
	
	return Number(list, listNode.getLinePosition(), context);
}

Number Interpreter::visit(IfNode& ifNode)
{
	
	for (int i = 0; i < ifNode.cases->size(); i++) 
	{
		Number cond = visit(ifNode.cases->at(i).condition);
		int condition = 0;
		cond.getBool(condition);
		if (condition)
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

		if(!stepValue.getInt(step))
			return throwError("Invalid Type for FOR loop Step");
	}

	int i = 0;
	
	if(!startValue.getInt(i))
		return throwError("Invalid Type for FOR loop incrementer");



	int end = 0;
	if (!endValue.getInt(end))
		return throwError("Invalid Type for FOR loop target");

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

	int check = 1;
	while(check)
	{
		Number cond = visit(whileNode.case_->condition);
		if (!cond.getValue().has_value())
			check = 0;
		
		//Casts
		cond.getBool(check);
		
		visit(whileNode.case_->expression);

		if (counter > maxWhileSize)
			check = 0;
	
		++counter;
	}

	return Number();
}

Number Interpreter::visit(FuncNode& funcNode)
{
	if (funcNode.varType == "Grid") {
		//Argument Size Check
		if (funcNode.arguments->empty())
			return throwError("Expected Arguments: (Integer, Integer?) " + funcNode.getLinePosition()->represent());
		else if (funcNode.arguments->size() > 2)
			CW_CORE_WARN("Grid Function only takes in two parameters (Integer, Integer?). Only the first two will be used.");

		//Parameters of grid
		std::shared_ptr<Number> width = std::make_shared<Number>(visit(funcNode.arguments->at(0)));
		std::shared_ptr<Number> height = nullptr;
		try 
		{
			height = std::make_shared<Number>(visit(funcNode.arguments->at(1)));
		}catch (...){}

		//Make grid
		std::shared_ptr<Grid> grid = std::make_shared<Grid>(width, height);

		//Set grid in context
		if(funcNode.varName != "")
			context->symbolTable->set(funcNode.varName, grid, funcNode.varType);

		return Number(grid, funcNode.getLinePosition(), context);
	}
	else if (funcNode.varType == "Run") 
	{
		//Argument Size Check
		if (funcNode.arguments->empty())
			return throwError("Expected Arguments: (Grid, Integer)|" + funcNode.getLinePosition()->represent());
		else if (funcNode.arguments->size() > 2)
			CW_CORE_WARN("Run Function only takes in two parameters (Grid, Integer). Only the first will be used. ");

	
		//Get Grid
		std::shared_ptr<Grid> grid = findGrid(funcNode);

		if (grid == nullptr) {
			return throwError("Expected a Grid in Function: " + funcNode.represent());
		}

		//Set Run Time
		std::shared_ptr<Number> time;
		try {
			 time = std::make_shared<Number>(visit(funcNode.arguments->at(1)));
		}
		catch (...) 
		{
			return throwError("Expected an integer (Seconds of Running). ");
		}

		//Play
		grid->play(time);
		
		//End Game
		return Number(grid, funcNode.getLinePosition(), context);
		
	}
	else if (funcNode.varType == "Delay") 
	{
		//Argument Size Check
		if (funcNode.arguments->empty())
			return throwError("Expected Arguments: " + funcNode.getLinePosition()->represent());
		else if (funcNode.arguments->size() > 2)
			CW_CORE_WARN("Delay Function only takes in two parameters (Grid, Integer). Only the first will be used. ");

		//Get Grid
		std::shared_ptr<Grid> grid = findGrid(funcNode);

		if (grid == nullptr) {
			return throwError("Expected a Grid in Function: " + funcNode.represent());
		}

		//Set Delay
		std::shared_ptr<Number> delay;
		try {
			delay = std::make_shared<Number>(visit(funcNode.arguments->at(1)));
		}
		catch (...)
		{
			return throwError("Expected an integer (In Milliseconds) for time of delay. ");
		}

		//Set Delay
		grid->setDelay(delay);

		//No return needed
	}
	else if (funcNode.varType == "Cell")
	{
		//Argument Size Check
		if (funcNode.arguments->empty())
			return throwError("Expected Arguments: (Grid, String, String) " + funcNode.getLinePosition()->represent());
		else if (funcNode.arguments->size() > 3)
			CW_CORE_WARN("Cell Function only takes in three parameters (Grid, String, String). Only the first three will be used.");

		//Get Grid
		std::shared_ptr<Grid> grid = findGrid(funcNode);

		std::shared_ptr<Number> dead;
		try {
			dead = std::make_shared<Number>(visit(funcNode.arguments->at(1)));
		}
		catch (...)
		{
			return throwError("Expected an integer (In Milliseconds) for time of delay. ");
		}

		std::shared_ptr<Number> alive;
		try {
			alive = std::make_shared<Number>(visit(funcNode.arguments->at(2)));
		}
		catch (...)
		{
			return throwError("Expected an integer (In Milliseconds) for time of delay. ");
		}

		grid->changeRepresentation(dead, alive);

	}
	else if(funcNode.varType == "Clear")
	{
		//Clears Screen
		system("cls");
	}
	

	//No Func Found
	return Number();
}

std::shared_ptr<Grid> Interpreter::findGrid(FuncNode& funcNode)
{
	string varName = funcNode.arguments->at(0)->getToken().svalue;

	std::shared_ptr<std::pair<string, std::any>> pair_val = context->symbolTable->get(varName);

	string type_name = context->symbolTable->get(varName)->first;

	std::shared_ptr<Grid> grid;
	if (type_name != "Grid")
	{
		Number num = visit(funcNode.arguments->at(0));
		try
		{
			grid = any_cast<std::shared_ptr<Grid>>(num.getValue());
		}
		catch (...) {

			return nullptr; 
		}
	}
	else
	{
		grid = any_cast<std::shared_ptr<Grid>>(context->symbolTable->get(varName)->second);
	}

	return grid;
}

Number Interpreter::visit(MakeAlive& makeAliveNode)
{

	string varName = makeAliveNode.gridName;
	std::shared_ptr<std::pair<string, std::any>> pair_val = context->symbolTable->get(varName);

	string type_name = context->symbolTable->get(varName)->first;

	if (type_name != "Grid")
	{
		return throwError("Expected a Grid in Function: " + makeAliveNode.represent());
	}

	std::shared_ptr<Grid> grid = std::any_cast<std::shared_ptr<Grid>>(pair_val->second);

	
	Number n = visit(makeAliveNode.aliveTable);

	std::shared_ptr<List> l;

	if (!n.getList(l))
		return throwError("Exepected a List");


	shared_ptr<vector<std::shared_ptr<List>>> lists = std::make_shared<vector<shared_ptr<List>>>();
	
	try {
		for (int i = 0; i < l->getValues()->size(); i++) {
			lists->push_back(any_cast<std::shared_ptr<List>>(l->getValues()->at(i).getValue()));
		}
	}
	catch (...) 
	{
		return throwError("Exepected a List of List");
	}


	grid->makeAlive(lists);

	return Number(grid, makeAliveNode.getLinePosition(), context);
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
