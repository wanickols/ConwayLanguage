#pragma once

class LinePosition;
class Context;
class Grid;
class List;

class Number
{
public:
	Number(std::any value, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context);
	Number();

	std::any  added_to(Number other);
	std::any  subbed_by(Number other);
	std::any  multed_by(Number other);
	std::any  power_of(Number other);
	std::any  dived_by(Number other);
	bool getComparison_EE(Number other);
	bool getComparison_NE(Number other);
	bool getComparison_LT(Number other);
	bool getComparison_GT(Number other);
	bool getComparison_LTE(Number other);
	bool getComparison_GTE(Number other);
	bool getComparison_KEYWORD(Number other, string keyword);
	bool notted();

	//Casting Functions
	bool getInt(int& valueHolder);
	bool getBool(int& valueHolder);
	bool getString(string& valueHolder);
	bool getList(std::shared_ptr<List>& valueHolder);
	bool getGrid(std::shared_ptr<Grid>& gridHolder);

	//Accessors
	const std::any getValue() const;
	void setValue(const std::any val);
	const bool getIsReal() const;
	void setIsReal(const bool real);

	const string represent();

	const std::shared_ptr<LinePosition> getPosition() const;
private:
	std::any value;
	bool isReal;
	std::shared_ptr<LinePosition> position;
	std::shared_ptr<Context> context;

};





