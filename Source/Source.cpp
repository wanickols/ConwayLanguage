#include "pch.h"
#include "Lexer.h"

//Conways game of life
/*
Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
All other live cells die in the next generation. Similarly, all other dead cells stay dead.
*/

//TODO Design syntax and semantics for a programming language that can run Conway's game of life
//TODO Provide a prototype implementation of a run-time system that is able to execute a simulation for input based on your programming - language specification.
//Note:: I want to have this be imported via a file, and then implemented in c++
//Note2:: Unlike my initial impression, the programming languange must be specific to this game, capable of making this game or extending it on a language level. 

/*
What do we need. 
The ability to make a class cell with the ability to be set alive or dead. 
The ability to set gridsize
The abilitiy to start and stop the game
The ability to set a number of runs (times game will continue until stop)
*/

void run(Lexer& lexer);

int main() {

	//Input
	string text = "2 * 5";
	string fileName = "Custom Input";

	//Lexer
	Lexer lexer(text, fileName);
	
	//Making Of Tokens
	run(lexer);
	vector<Token> tokens = lexer.getTokens();


	//Printing of tokens
	for (int i = 0; i < tokens.size(); i++)
	{
		cout << tokens.at(i).Representation();
	}

	return 0;
}

void run(Lexer& lexer)
{
	lexer.make_tokens();
}
