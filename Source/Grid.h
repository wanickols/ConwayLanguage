#pragma once

class Cell;
class Number;
class List;

class Grid
{
private:
	//Init Fucntions
	void InitCells();
	void InitAliveTable();
	void calculateNeighbors();

public:
	//Constructor
	Grid(std::shared_ptr<Number> width, std::shared_ptr<Number> height = nullptr);

	//Functions
	void makeAlive(std::shared_ptr<std::vector<List>> aliveTable);
	void calculateAlive();
	void play(std::shared_ptr<Number> time);
	void expand(Number size); //increases size by number
	void shrink(Number size); //decreases size by number

	//Accessors
	void setWidthHeight(std::shared_ptr<Number> width, std::shared_ptr<Number> height = nullptr);
	const string represent();
	void setDelay(std::shared_ptr<Number> delay);
	const shared_ptr<vector<vector<shared_ptr<Cell>>>> getGrid() const;

private:
	//Variables
	shared_ptr <vector <vector <shared_ptr <Cell>>>> grid; //Grid of Cells
	int width; 
	int height;
	int delayTime;
	std::shared_ptr<vector<vector<bool>>> aliveTable;
};

