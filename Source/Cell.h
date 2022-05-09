#pragma once
class Cell
{
public:
	//Constructor
	Cell(bool isAlive, string& dead, string& alive);

	//Functions
	void calculateAlive();
	void calculateNeighbors(shared_ptr<vector<vector<shared_ptr<Cell>>>> grid, int myHeight, int myWidth);
	const string& representation();

	//Accessors
	const bool getAlive() const;
	void changeRepresentation(string& dead, string& alive);
	void setAlive(const bool alive);
private:
	//Variables
	vector<shared_ptr<Cell>> neighbors; // List of neighbor cells
	bool currAlive; //Current Alive
	string& dead; 
	string& alive;
	bool nextAlive; //Alive For Next Cycle
};

