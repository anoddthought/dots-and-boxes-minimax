#include "Square.h"
#include "Line.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;


Square::~Square()
{
}

////Square Member Functions////
bool Square::capture(string s, int sqrNum, Line horLine[XGRID][YGRID+1], Line verLine[XGRID+1][YGRID])
{
	//square less than XGRID*YGRID(amount of squares)
	if (sqrNum >= 0 && sqrNum < XGRID*YGRID)
	{
		//if all lines of the square are captured then the square becomes captured
		if ((top->getOn() && bottom->getOn() && left->getOn() && right->getOn()) && on != true)
		{
			//set square attributes
			owner = s;
			on = true;
			//cout << "\nYou captured a square! You may go again!\n";
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

bool Square::lineIsInSquare(Line *tmp)
{
	//if the line is one of the lines of this square
	if ((tmp == left) || (tmp == right) || (tmp == top) || (tmp == bottom))
	{
		return true;
	}
	else return false;
}
