#pragma once

class Node;

class Case
{
public:

	Case(std::shared_ptr<Node> condition, std::shared_ptr<Node> expression); //Object that holds two Nodes.

	//Variables
	std::shared_ptr<Node> condition; 
	std::shared_ptr<Node> expression;
};

