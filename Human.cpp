#include "Human.h"
#include <iostream>
using namespace std;

Human::Human()
{
}


Human::~Human()
{
}

string Human::getMove()
{
	nextMove = "";
	//ask for player input
	cout << endl << endl << "What is your next move?(example a1a2 or A1B1): ";
	cin >> nextMove;

	return nextMove;
}