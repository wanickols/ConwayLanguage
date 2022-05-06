#pragma once

class Number;

class List
{
public:

	List(std::shared_ptr<std::vector<std::any>> value, string type);

	List added_to(std::any value, string type);

	void remove(std::shared_ptr<Number> index);
	std::any retrieve(std::shared_ptr<Number> index);
	
	const string& getValueType() const;
	const std::shared_ptr<std::vector<std::any>> getValues() const;

private:
	string valueType;
	std::shared_ptr<std::vector<std::any>> values;
};

