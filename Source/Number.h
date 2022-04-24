#pragma once

class LinePosition;
class Context;

class Number
{
public:
	Number(int value, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context);

	int added_to(Number other);
	int subbed_by(Number other);
	int multed_by(Number other);
	int power_of(Number other);
	int dived_by(Number other);

	const int getValue() const;
	void setValue(const int val);
	const std::shared_ptr<LinePosition> getPosition() const;
private:
	int value;
	std::shared_ptr<LinePosition> position;
	std::shared_ptr<Context> context;

};





