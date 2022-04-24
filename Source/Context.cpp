#include "pch.h"
#include "Context.h"

Context::Context(string name, std::shared_ptr<Context> parent_context, std::shared_ptr<LinePosition> entry_position) : name(name), parentContext(parent_context), entryPosition(entry_position)
{
}

const string Context::represent()
{
	stringstream ss;

	ss << name;
	if(parentContext)
		ss << "<-" << parentContext->represent();

	return ss.str();
}
