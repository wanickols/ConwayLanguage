#pragma once

class Number;

class List
{
public:

	List(std::shared_ptr<std::vector<Number>> value);

	List added_to(Number value);
	List concatenated(Number value);

	void remove(std::shared_ptr<Number> index);
	std::any retrieve(std::shared_ptr<Number> index);
	
	const std::shared_ptr<std::vector<Number>> getValues() const;

private:
	std::shared_ptr<std::vector<Number>> values;
};

