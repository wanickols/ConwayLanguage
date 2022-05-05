#pragma once

class LinePosition;
class Context;

class Number
{
public:
	Number(int value, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context);
	Number();

	int added_to(Number other);
	int subbed_by(Number other);
	int multed_by(Number other);
	int power_of(Number other);
	int dived_by(Number other);
	bool getComparison_EE(Number other);
	bool getComparison_NE(Number other);
	bool getComparison_LT(Number other);
	bool getComparison_GT(Number other);
	bool getComparison_LTE(Number other);
	bool getComparison_GTE(Number other);
	bool getComparison_KEYWORD(Number other, string keyword);
	bool notted();

	//Accessors
	const int getValue() const;
	void setValue(const int val);
	const bool getIsReal() const;
	void setIsReal(const bool real);

	const std::shared_ptr<LinePosition> getPosition() const;
private:
	int value;
	bool isReal;
	std::shared_ptr<LinePosition> position;
	std::shared_ptr<Context> context;

};





