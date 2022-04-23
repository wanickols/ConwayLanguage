#include "pch.h"
#include "Number.h"

Number::Number(int value) : value(value)
{
}


int Number::added_to(Number other)
{
	return value + other.value;
}

int Number::subbed_by(Number other)
{
	return value - other.value;
}

int Number::multed_by(Number other)
{
	return value * other.value;
}

int Number::dived_by(Number other)
{
	return value/other.value;
}

const int Number::getValue() const
{
	return value;
}

void Number::setValue(const int val)
{
	value = val;
}
