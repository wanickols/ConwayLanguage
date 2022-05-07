#include "pch.h"
#include "Cell.h"

Cell::Cell(bool alive) : currAlive(alive), nextAlive(alive)
{
	neighbors.reserve(8); //We have 8 neighbors
}

void Cell::calculateAlive()
{
	int aliveCount = 0;

	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors.at(i)->currAlive)
			++aliveCount;
	}

	if (aliveCount == 3) // if 3 turn alive or stay alive
	{
		nextAlive = true;
	}
	else if (!currAlive)
	{
		nextAlive = false;
	}
	else if (aliveCount == 2) //if alive and 2 stay alive
	{
		nextAlive = true;
	}
	else //Over population, underpopulation, or not 3 to make alive
	{
		nextAlive = false;
	}

}

void Cell::calculateNeighbors(shared_ptr<vector<vector<shared_ptr<Cell>>>> grid, int myHeight, int myWidth)
{
	// x x x
	// x 0 x  
	// x x x
	// 0 is me, x are my neighbors
	if (myHeight != 0) //If not at top
	{

		neighbors.emplace_back(grid->at(myHeight - 1).at(myWidth)); // top middle

		if (myWidth != 0) //if Not at leftMost
			neighbors.emplace_back(grid->at(myHeight - 1).at(myWidth - 1)); // top left

		else if (myWidth < grid->at(0).size() - 1) // if not at rightMost
			neighbors.emplace_back(grid->at(myHeight - 1).at(myWidth + 1)); // top right
	}

	if (myHeight < grid->size() - 1) //If not at bottom
	{

		neighbors.emplace_back(grid->at(myHeight + 1).at(myWidth)); // bottom middle

		if (myWidth != 0)
			neighbors.emplace_back(grid->at(myHeight + 1).at(myWidth - 1)); // bottom left

		if (myWidth < grid->at(0).size() - 1)
			neighbors.emplace_back(grid->at(myHeight + 1).at(myWidth + 1)); // bottom right
	}

	if (myWidth != 0)
		neighbors.emplace_back(grid->at(myHeight).at(myWidth - 1)); // middle left

	if (myWidth < grid->at(0).size() - 1)
		neighbors.emplace_back(grid->at(myHeight).at(myWidth + 1)); // middle right

}

void Cell::setAlive(const bool alive)
{
	currAlive = nextAlive = alive;
}

const bool Cell::getAlive() const
{
	return currAlive;
}


const char Cell::representation()
{
	currAlive = nextAlive;
	if (currAlive)
	{
		return 'O';
	}
	else {
		return 'X';
	}
}

