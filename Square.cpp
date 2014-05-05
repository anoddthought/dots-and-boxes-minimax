#include "Square.h"
#include "Line.h"
#include <string>
#include <iostream>
using namespace std;


Square::~Square()
{
}

////Square Member Functions////
bool Square::capture(string s, int sqrNum, Line horLine[7][8], Line verLine[8][7])
{
	//square less than 49(amount of squares)
	if (sqrNum >= 0 && sqrNum < 50)
	{
		//if all lines of the square are captured then the square becomes captured
		if ((top->getOn() && bottom->getOn() && left->getOn() && right->getOn()) && on != true)
		{
			//set square attributes
			owner = s;
			on = true;
			cout << "\nYou captured a square! You may go again!\n";
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

//display player name on row one else display four spaces
void Square::display()
{
	//display first space
	cout << ' ';
	//next two spaces are either blank or player initials
	cout << this->getOwner();	//display initials for first row
	//display last space
	cout << ' ';
}

void Square::setLines(Line* l, Line* r, Line* t , Line* b)
{
	left = l;
	right = r;
	top = t;
	bottom = b;
}

int Square::linesLeftToCapture()
{
	int count = 4;
	if (left->getOn())
		count--;
	if (right->getOn())
		count--;
	if (top->getOn())
		count--;
	if (bottom->getOn())
		count--;
	return count;
}

Line* Square::lineNotCaught()
{
	if (!left->getOn())
		return left;
	if (!right->getOn())
		return right;
	if (!top->getOn())
		return top;
	return bottom;
}