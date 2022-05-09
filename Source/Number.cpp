#include "pch.h"
#include "Number.h"
#include "LinePosition.h"
#include "Context.h"
#include "List.h"
#include "Cell.h"
#include "Grid.h"

Number::Number(std::any value, std::shared_ptr<LinePosition> pos, std::shared_ptr<Context> context) : value(value), position(pos), context(context), isReal(true)
{
}

Number::Number() : value(0), position(nullptr), context(nullptr), isReal(false)
{
}


std::any Number::added_to(Number other)
{

	//Integer
	int thisVal = 0;
	int othVal = 0;
	try {
		thisVal = any_cast<int>(value);


		try {
			othVal = any_cast<int>(other.value);
		}
		catch (...)
		{
			CW_CORE_ERROR("Tried to add an Integer by a non Integer");
			return -1;
		}

		return thisVal + othVal;

	}
	catch (...) {}

	//List
	std::shared_ptr<List> thisList;
	if (getList(thisList))
	{
		return thisList->added_to(other);
	}
	//Grid
	std::shared_ptr<Grid> grid;
	if(getGrid(grid))
	{
		grid->expand(other);
		return grid;
	}

	//Error
	CW_CORE_ERROR("A + Operator Does Not exist for this type");
	return -1;
}

std::any Number::subbed_by(Number other)
{
	//Integer
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);

		int othVal = 0;
		try {
			othVal = any_cast<int>(other.value);
		}
		catch (...)
		{
			CW_CORE_ERROR("Tried to subtract an Integer by a non Integer");
			return -1;
		}

		return thisVal - othVal;
	}
	catch (...){}


	//List
	std::shared_ptr<List> thisList;
	if (getList(thisList))
	{
		thisList->remove(std::make_shared<Number>(other));
		return thisList;
	}
	//Grid
	std::shared_ptr<Grid> grid;
	if (getGrid(grid))
	{
		grid->shrink(other);
		return grid;
	}


	//Error
	CW_CORE_ERROR("A - Operator Does Not exist for this type");
	return -1;
}

std::any  Number::multed_by(Number other)
{
	//integer
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);

		int othVal = 0;
		try {
			othVal = any_cast<int>(other.value);
		}
		catch (...)
		{
			CW_CORE_ERROR("Tried to multiply an Integer by a non Integer");
			return -1;
		}
		return thisVal * othVal;
	}
	catch (...) {}



	//List
	std::shared_ptr<List> thisList;
	if (getList(thisList))
	{
		return thisList->concatenated(other);
	}

	//Grid multiply size

	//Error
	CW_CORE_ERROR("A * Operator Does Not exist for this type");
	return -1;

	
}

std::any Number::power_of(Number other)
{
	
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_ERROR("A ^ Operator Does Not exist for this type");
		return -1;
	}

	int othVal = 0;
	try {
		othVal = any_cast<int>(other.value);
	}
	catch (...)
	{
		CW_CORE_ERROR("Tried to raise to an invalid Power type");
		return -1;
	}

	
	if (othVal < 0)
		CW_CORE_WARN("Negative Powers will be 0 with Ints");

	return (int)std::pow(thisVal, othVal);
	
}

std::any Number::dived_by(Number other)
{
	
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);

		
		//}
		int othVal = 0;
		try {
			othVal = any_cast<int>(other.value);
		}
		catch (...)
		{
			CW_CORE_ERROR("Tried to divide an Integer by a non Integer");
			return -1;
		}

		return thisVal / othVal;
	}
	catch (...) {}
	
	//List
	std::shared_ptr<List> thisList;
	if (getList(thisList))
	{
		return thisList->retrieve(std::make_shared<Number>(other));
	}
	//Grid
	std::shared_ptr<Grid> grid;
	if (getGrid(grid))
	{
		grid->shrink(other);
		return grid;
	}

	CW_CORE_ERROR("A / Operator Does Not exist for this type");
	return -1;
	
	
}

bool Number::getComparison_EE(Number other)
{
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_WARN("No == defined for TYPE given");
		
		return 0;
	}

	int othVal = 0;
	try {
		othVal = any_cast<int>(other.value);
	}
	catch (...)
	{
		CW_CORE_WARN("No == defined for INT == UNKNOWN");
		return 0;
	}

	return thisVal == othVal;
	
}

bool Number::getComparison_NE(Number other)
{
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_WARN("No != defined for TYPE given");

		return 0;
	}

	int othVal = 0;
	try {
		othVal = any_cast<int>(other.value);
	}
	catch (...)
	{
		CW_CORE_WARN("No != defined for INT != UNKNOWN");
		return 0;
	}

	return thisVal != othVal;
}

bool Number::getComparison_LT(Number other)
{
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_WARN("No < defined for TYPE given");

		return 0;
	}

	int othVal = 0;
	try {
		othVal = any_cast<int>(other.value);
	}
	catch (...)
	{
		CW_CORE_WARN("No < defined for INT < UNKNOWN");
		return 0;
	}

	return thisVal < othVal;
}

bool Number::getComparison_GT(Number other)
{
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_WARN("No > defined for TYPE given");

		return 0;
	}

	int othVal = 0;
	try {
		othVal = any_cast<int>(other.value);
	}
	catch (...)
	{
		CW_CORE_WARN("No > defined for INT > UNKNOWN");
		return 0;
	}

	return thisVal > othVal;
}

bool Number::getComparison_LTE(Number other)
{
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_WARN("No <= defined for TYPE given");

		return 0;
	}

	int othVal = 0;
	try {
		othVal = any_cast<int>(other.value);
	}
	catch (...)
	{
		CW_CORE_WARN("No <= defined for INT <= UNKNOWN");
		return 0;
	}

	return thisVal <= othVal;
}

bool Number::getComparison_GTE(Number other)
{
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_WARN("No >= defined for TYPE given");

		return 0;
	}

	int othVal = 0;
	try {
		othVal = any_cast<int>(other.value);
	}
	catch (...)
	{
		CW_CORE_WARN("No >= defined for INT >= UNKNOWN");
		return 0;
	}

	return thisVal >= othVal;
}

bool Number::getComparison_KEYWORD(Number other, string keyword)
{
	if (keyword == "AND") {
		int thisVal = 0;
		int othVal = 0;
		try {
			thisVal = any_cast<int>(value);
			othVal = any_cast<int>(other.value);
		}
		catch (...)
		{
			CW_CORE_WARN("No AND defined for TYPES given");
			return 0;
		}
		return thisVal && othVal;
	}
	else if (keyword == "OR") {
		int thisVal = 0;
		int othVal = 0;
		try {
			thisVal = any_cast<int>(value);
			othVal = any_cast<int>(other.value);
		}
		catch (...)
		{
			CW_CORE_WARN("No OR defined for TYPES given");
			return 0;
		}

		return thisVal || othVal;
	}
	else
		return 0;
}

bool Number::notted()
{
	int thisVal = 0;
	try {
		thisVal = any_cast<int>(value);
	}
	catch (...)
	{
		CW_CORE_WARN("No NOT defined for TYPE given");
		return 0;
	}

	if (thisVal == 0)
		return 1;
	
	return 0;
}

bool Number::getInt(int& valueHolder)
{
	try { 
		valueHolder = any_cast<int>(value);
		return true;
	}
	catch (...) {
		return false;
	}
}

bool Number::getString(string& valueHolder)
{
	try {
		valueHolder = any_cast<string>(value);
		return true;
	}
	catch (...) {
		return false;
	}
}

bool Number::getList(std::shared_ptr<List>& listHolder)
{
	try {
		listHolder = any_cast<std::shared_ptr<List>>(value);
		return true;
	}
	catch (...) {
		return false;
	}
}

bool Number::getGrid(std::shared_ptr<Grid>& gridHolder)
{
	try {
		gridHolder = any_cast<std::shared_ptr<Grid>>(value);
		return true;
	}
	catch (...) {
		return false;
	}
}

const std::any Number::getValue() const
{
	return value;
}

void Number::setValue(const std::any val)
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

const string Number::represent()
{

	//Integer
	int thisVal = 0;
	
	if(getInt(thisVal))
	{
		stringstream ss;
		ss << thisVal;
		return ss.str();
	}

	//Chars/Strings
	string stringVal;
	if(getString(stringVal))
	{
		return stringVal;
	}

	Cell* cell;
	try
	{
		cell = new Cell(any_cast<Cell>(value));

		stringstream ss;
		ss << cell->representation();
		delete cell;
		return ss.str();
	}
	catch (...) {}


	//Grid
	std::shared_ptr<Grid> grid;
	if(getGrid(grid))
	{
		grid = any_cast<std::shared_ptr<Grid>>(value);

		stringstream ss;
		ss << grid->represent();
		return ss.str();
	}
	//List
	std::shared_ptr<List> thisList;

	if(getList(thisList))
	{
		stringstream ss;

		ss << '[';
		for (int i = 0; i < thisList->getValues()->size() - 1; i++) { //List prints each value 
			ss << thisList->getValues()->at(i).represent() << ", ";
		}
		ss << thisList->getValues()->back().represent() << ']';

		return ss.str();
	}


	//No Valid Type Found
	return " ";
}

const std::shared_ptr<LinePosition> Number::getPosition() const
{
	return position;
}
