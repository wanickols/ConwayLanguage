#include "pch.h"
#include "Grid.h"
#include "Cell.h"
#include "Number.h"

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

void Grid::makeAlive(std::shared_ptr<std::vector<std::vector<bool>>> aliveTable)
{
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