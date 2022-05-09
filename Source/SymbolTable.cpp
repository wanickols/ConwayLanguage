#include "pch.h"
#include "SymbolTable.h"

SymbolTable::SymbolTable() : ParentSymbol(nullptr)
{
	symbolsDictionary = std::make_shared<unordered_map<string, std::shared_ptr<std::pair<string, std::any>>>>();
}

//Returns a pair with a value and its type
std::shared_ptr<std::pair<string, std::any>> SymbolTable::get(string variableName)
{
	if (symbolsDictionary->find(variableName) != symbolsDictionary->end())
	{
		std::shared_ptr<std::pair<string, std::any>> result = std::make_shared<std::pair<string, std::any>>(symbolsDictionary->find(variableName)->second->first, symbolsDictionary->find(variableName)->second->second);
		return result;
	}
	else if (ParentSymbol != nullptr)
	{
		//Parents variable
		return ParentSymbol->get(variableName);
	}
	else 
	{
		return std::make_shared<std::pair<string, std::any>>("null", NULL);
	
	}

}

//Sets value in hash
void SymbolTable::set(string name, std::any value, string type)
{

	auto it = symbolsDictionary->find(name);
	if (it != symbolsDictionary->end()) {
		if(it->second->first != type)
		{
			CW_CORE_WARN("Warning! Overiding variable type of variable: {}", name);
		}

		std::shared_ptr<std::pair<string, std::any>> symbol = std::make_shared<std::pair<string, std::any>>(type, value);
		it->second = symbol;
	
	}
	else
		symbolsDictionary->insert(std::pair< string, std::shared_ptr<std::pair<string, std::any>>>(name, std::make_shared<std::pair<string, std::any>>(type, value)));
}

//Removes value if exists
void SymbolTable::remove(string name)
{
	if (symbolsDictionary->find(name) != symbolsDictionary->end())
	{
		symbolsDictionary->erase(name);
	}
	else 
	{
		CW_CORE_WARN("SymbolTable: remove called but Symbol not Found.");
	}
}
