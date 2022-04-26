#pragma once

class LinePosition;
class SymbolTable;

class Context
{
public:
	Context(string name, std::shared_ptr<Context> parent_context, std::shared_ptr<LinePosition> entry_position);
	
	const string represent();

	std::shared_ptr<SymbolTable> symbolTable; //Variable Storage Table

private:
	//Variables
	string name;
	std::shared_ptr<Context> parentContext;
	std::shared_ptr<LinePosition> entryPosition;
};

