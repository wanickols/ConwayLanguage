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
            grid->at(i).emplace_back(std::make_shared<Cell>(false, dead, alive));
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


Grid::Grid(std::shared_ptr<Number> N_width, std::shared_ptr<Number> N_height) : delayTime(400), dead("X"), alive("O")
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

    if (!N_width->getInt(height))
    {
        CW_CORE_ERROR("Expected an INT for width");
    }

    if (!N_height->getInt(width))
    {
        CW_CORE_ERROR("Expected an INT for height");
    }

}

void Grid::makeAlive(std::shared_ptr<std::vector<shared_ptr<List>>> listTable)
{

    //Size Error Check
    if (listTable->size() > width || (!listTable->empty() && listTable->at(0)->getValues() != nullptr && listTable->at(0)->getValues()->size() > height))
    {
        CW_CORE_ERROR("Cannot Put in a List Larger than Grid");
        return;
    }

    //Trying to get values from vector of list
    try {
        for (int i = 0; i < listTable->size(); i++) {

            for (int j = 0; j < listTable->at(i)->getValues()->size(); j++) {
                aliveTable->at(i).at(j) = (bool)any_cast<int>(listTable->at(i)->getValues()->at(j).getValue());
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

void Grid::play(std::shared_ptr<Number> time)
{
    float count = 1;
    int counter = 0;
    if (time->getInt(counter))
    {
        count = (float)counter;
    }
    else 
    {
        CW_CORE_ERROR("Invalid Value for Time. Expected an integer.");
        return;
    }

    count *= (1000.f/delayTime); //Convert Seconds based on delayTime in milliseconds increments
  
    //Runs game for set count
    for (int i = 0; i < count; i++)
    {
 
        system("cls");
        cout << represent();
        cout << "Cycles Remaining: " << count - i - 1;
        Sleep(delayTime);
        calculateAlive();
       
    }
    cout << "Cycles Remaining: " << 0;
    system("cls");
}

void Grid::expand(Number size)
{
    int expansion = 0;
    if (size.getInt(expansion)) 
    {
        width += expansion;
        height += expansion;
        grid->clear();
        InitCells();
    }
    else 
    {
        CW_CORE_ERROR("Invalid Value Expanding Grid. Expected an integer.");
    }

}

void Grid::shrink(Number size)
{
    int shrink = 0;
    if (size.getInt(shrink))
    {
        width -= shrink;
        height -= shrink;
        grid->clear();
        InitCells();
    }
    else
    {
        CW_CORE_ERROR("Invalid Value Shrinking Grid. Expected an integer.");
    }
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
    ss << "\n";
    return ss.str();
}

void Grid::setDelay(std::shared_ptr<Number> delay)
{
    int newTime = 0;
    
    //Cast
    if(!delay->getInt(newTime)){
        CW_CORE_WARN("Invalid Delay Type. Expected an Integer. Delay not set");
        return;
    }

    delayTime = newTime;
}

void Grid::changeRepresentation(std::shared_ptr<Number> dead, std::shared_ptr<Number> alive)
{
    if (!dead->getString(this->dead)) 
    {
        CW_CORE_WARN("Invalid Death Representation. Expected a Char. Representation not set");
        return;
    }

    if (!alive->getString(this->alive))
    {
        CW_CORE_WARN("Invalid Alive Representation. Expected a Char. Representation not set");
        return;
    }
}

const shared_ptr<vector<vector<shared_ptr<Cell>>>> Grid::getGrid() const
{

    return grid;
}