#include "pch.h"
#include "Number.h"
#include "LinePosition.h"
#include "Context.h"

Number::Number(int value, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context) : value(value), position(pos), context(context)
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
	return std::pow(value, other.value);
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

const int Number::getValue() const
{
	return value;
}

void Number::setValue(const int val)
{
	value = val;
}

const std::shared_ptr<LinePosition> Number::getPosition() const
{
	return position;
}
