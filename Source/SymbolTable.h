#pragma once

class SymbolTable
{
public:
	//Constructor
	SymbolTable();

	//Functions
	std::shared_ptr<std::pair<string, std::any>> get(string variableName);

	void set(string name, std::any value, string type = "Exists");

	void remove(string name);

	//Variables
	std::shared_ptr<SymbolTable> ParentSymbol;
private:
	std::shared_ptr<unordered_map<string, std::shared_ptr<std::pair<string, std::any>>>> symbolsDictionary;

};

