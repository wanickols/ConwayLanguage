#pragma once


class Number
{
public:
	Number(int value);

	int added_to(Number other);
	int subbed_by(Number other);
	int multed_by(Number other);
	int dived_by(Number other);

	const int getValue() const;
	void setValue(const int val);

private:
	int value;
};





