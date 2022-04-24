#include "pch.h"
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Number.h"
#include "Context.h"
#include "LinePosition.h"

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

void run(string& text, string& fileName);
std::shared_ptr<string> userInput();
std::shared_ptr<string> fileInput();
bool Init();
//void PrintRun(vector<Token>& tokens, Parser& parser);

int main() {

	//Init
	Init();

	//Input
	std::shared_ptr<string> text = userInput();
	string fileName = "Custom Input";
	
	

	//Running
	run(*text, fileName);
	 
	return 0;
}

void run(string& text, string& fileName)
{

	vector<Token> tokens;

	//Lexer
	Lexer lexer(text, fileName);
	//Generate Tokens
	lexer.make_tokens();
	
	tokens = lexer.getTokens();

	Parser parser(tokens);
	
	

	std::shared_ptr<Node> parsedNode = parser.parse();

	//Context
	std::shared_ptr<LinePosition> linePos = std::make_shared<LinePosition>(0, 0, 0, fileName);
	std::shared_ptr<Context> context = std::make_shared<Context>("Main", nullptr, linePos);

	//Interpretation
	Interpreter interper(context);

	//Printing
	cout << "Here's what we made: \n";
	cout << interper.visit(parsedNode).getValue();

	//PrintRun(tokens, parser);
}

std::shared_ptr<string> userInput()
{
	std::shared_ptr<string> text = std::make_shared<string>();
	
	//Prompt
	std::cout << "Hello and welcome to conway programming! Please enter in your code below \n";
	
	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
		*text += line + " ";

	CW_CORE_WARN(*text);
	//Working on it
	std::cout << "Alrighty! just a moment... \n";

	return text;
}

std::shared_ptr<string> fileInput()
{

	//TODO
	//open file
	//get contents as string
	//
	//return string to be run
	return std::shared_ptr<string>();
}

bool Init()
{
	//Logger
	Conway::Log log;
	log.Init();

	return true;
}

void PrintRun(vector<Token>& tokens, Parser& parser)
{
	

	//Printing of tokens
	for (int i = 0; i < tokens.size(); i++)
	{
		cout << tokens.at(i).Representation();
	}

	cout << "\n";
}