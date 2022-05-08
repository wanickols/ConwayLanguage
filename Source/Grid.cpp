#include "pch.h"
#include "Grid.h"
#include "Cell.h"
#include "Number.h"
#include "List.h"

void Grid::InitCells()
{
    //Reserve sizes to prevent copies
    grid->reserve(width);
    for (int i = 0; i < width; i++)
    {
        grid->emplace_back(vector<shared_ptr<Cell>>());
        grid->at(i).reserve(height);
    }

    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < height; j++)
        {
            grid->at(i).emplace_back(std::make_shared<Cell>(false));
        }
    }
}

void Grid::InitAliveTable()
{
    //Table
    aliveTable = std::make_shared<vector<vector<bool>>>();

   //Table Init
    aliveTable->reserve(width);
    for (int i = 0; i < width; i++)
    {
        aliveTable->emplace_back(vector<bool>());
        aliveTable->at(i).reserve(height);
    }

    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < height; j++)
        {
            aliveTable->at(i).emplace_back(false);
        }
    }

}

void Grid::calculateNeighbors()
{
    //Made neighbors for every cell
    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < grid->at(i).size(); j++)
        {
            grid->at(i).at(j)->calculateNeighbors(grid, i, j);
        }
    }
}


Grid::Grid(std::shared_ptr<Number> N_width, std::shared_ptr<Number> N_height)
{
    //Set width and height
    if (!N_height)
        N_height = N_width;

    setWidthHeight(N_width, N_height);

    //Init grid
    grid = std::make_shared<vector<vector<shared_ptr<Cell>>>>();

    //Make Grid of dead cells
    InitCells();

    //Makes table of bools for makeAlive to reuse
    InitAliveTable();

    //Attach Neighbors
    calculateNeighbors();

}

void Grid::setWidthHeight(std::shared_ptr<Number> N_width, std::shared_ptr<Number> N_height)
{
    try
    {
        height = any_cast<int>(N_width->getValue());
    }
    catch (...)
    {
        CW_CORE_ERROR("Expected an INT for width");
    }

    try
    {
        width = any_cast<int>(N_height->getValue());
    }
    catch (...)
    {
        CW_CORE_ERROR("Expected an INT for height");
    }
}

void Grid::makeAlive(std::shared_ptr<std::vector<List>> listTable)
{

    //Size Error Check
    if (listTable->size() > width || (!listTable->empty() && listTable->at(0).getValues() != nullptr && listTable->at(0).getValues()->size() > height))
    {
        CW_CORE_ERROR("Cannot Put in a List Larger than Grid");
        return;
    }

    //Trying to get values from vector of list
    try {
        for (int i = 0; i < listTable->size(); i++) {

            for (int j = 0; j < listTable->at(i).getValues()->size(); j++) {
                aliveTable->at(i).at(j) = (bool)any_cast<int>(listTable->at(i).getValues()->at(j).getValue());
            }
        }
    }
    catch (...)
    {
        CW_CORE_ERROR("Exepected a List of List of Bools");
        return; 
    }

    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < grid->at(i).size(); j++)
        {
            grid->at(i).at(j)->setAlive(aliveTable->at(i).at(j));
        }
    }
}

void Grid::calculateAlive()
{

    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < grid->at(i).size(); j++)
        {
            grid->at(i).at(j)->calculateAlive();
        }
    }
}

void Grid::expand(Number size)
{
}

void Grid::shrink(Number size)
{
}



const string Grid::represent()
{
    stringstream ss;
    //Made neighbors for every cell
    for (int i = 0; i < grid->size(); i++)
    {
        ss << "\n";
        for (int j = 0; j < grid->at(i).size() - 1; j++)
        {
            ss << grid->at(i).at(j)->representation() << " ";
        }
        ss << grid->at(i).back()->representation();
    }
    return ss.str();
}

const shared_ptr<vector<vector<shared_ptr<Cell>>>> Grid::getGrid() const
{

    return grid;
}