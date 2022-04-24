#pragma once

class LinePosition;

class Context
{
public:
	Context(string name, std::shared_ptr<Context> parent_context, std::shared_ptr<LinePosition> entry_position);
	
	const string represent();

private:
	//Variables
	string name;
	std::shared_ptr<Context> parentContext;
	std::shared_ptr<LinePosition> entryPosition;
};

