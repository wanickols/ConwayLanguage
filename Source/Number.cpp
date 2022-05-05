#include "pch.h"
#include "Number.h"
#include "LinePosition.h"
#include "Context.h"

Number::Number(int value, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context) : value(value), position(pos), context(context), isReal(true)
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

int Number::power_of(Number other)
{
	if(other.value < 0)
		CW_CORE_WARN("Negative Powers will be 0 with Ints");
	return (int)std::pow(value, other.value);
}

int Number::dived_by(Number other)
{
	if (other.value == 0) {
		string details = "Division by 0! See {}/0 ";
		RTError error(details, position, context);

		CW_CORE_ERROR( error.as_string(), value);
		other.value = 1;
	}
	return value/other.value;
}

bool Number::getComparison_EE(Number other)
{
	return value == other.value;
}

bool Number::getComparison_NE(Number other)
{
	return value != other.value;
}

bool Number::getComparison_LT(Number other)
{
	return value < other.value;
}

bool Number::getComparison_GT(Number other)
{
	return value > other.value;
}

bool Number::getComparison_LTE(Number other)
{
	return value <= other.value;
}

bool Number::getComparison_GTE(Number other)
{
	return value >= other.value;
}

bool Number::getComparison_KEYWORD(Number other, string keyword)
{
	if (keyword == "AND")
		return value && other.value;
	else if (keyword == "OR")
		return value || other.value;
	else
		return 0;
}

bool Number::notted()
{
	if (value == 0)
		return 1;
	else
		return 0;
}

const int Number::getValue() const
{
	return value;
}

void Number::setValue(const int val)
{
	value = val;
}

const bool Number::getIsReal() const
{
	return isReal;
}

void Number::setIsReal(const bool real)
{
	isReal = real;
}

const std::shared_ptr<LinePosition> Number::getPosition() const
{
	return position;
}
