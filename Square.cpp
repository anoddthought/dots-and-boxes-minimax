#include "Square.h"

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

vector<Line*> Square::linesNotCaught()
{
	vector<Line*> tmp;
	if (!left->getOn())
		tmp.push_back(left);
	if (!right->getOn())
		tmp.push_back(right);
	if (!top->getOn())
		tmp.push_back(top);
	if (!bottom->getOn())
		tmp.push_back(bottom);
	return tmp;
}

bool Square::containsLine(Line *tmp)
{
	if (tmp == left)
		return true;
	if (tmp == right)
		return true;
	if (tmp == top)
		return true;
	if (tmp == bottom)
		return true;
	return false;
}