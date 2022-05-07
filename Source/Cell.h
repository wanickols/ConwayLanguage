#pragma once
class Cell
{
public:
	//Constructor
	Cell(bool alive);

	//Functions
	void calculateAlive();
	void calculateNeighbors(shared_ptr<vector<vector<shared_ptr<Cell>>>> grid, int myHeight, int myWidth);
	const char representation();

	//Accessors
	const bool getAlive() const;
	void setAlive(const bool alive);
private:
	//Variables
	vector<shared_ptr<Cell>> neighbors; // List of neighbor cells
	bool currAlive; //Current Alive
	bool nextAlive; //Alive For Next Cycle
};

