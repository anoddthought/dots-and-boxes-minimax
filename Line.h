#pragma once
#include <string>
#include "Square.h"
using namespace std;

class Line
{
	bool on;								//false for off, true for on
	string owner;							//contains owner's name
	int x, y;								//line coordinates
	char char1, char2;
	int int1, int2;
	int type;								//0 = horizontal, 1 = vertical
	Square *first, *second;
public:
	Line() { on = false, owner = ""; }		//constructor no parameters
	~Line();
	void hdisplay();						//for use in displaying horizontal lines
	void vdisplay();						//for use in displaying vertical lines
	void reset() { on = false; owner = ""; }//reset all variables
	bool capture(string);					//captures line if not already owned and returns true, if owned returns false
	bool getOn() { return on; }				//returns boolean varaiable on
	void setX(int tmp) { x = tmp; }			//setter and getters for X 
	int getX() { return x; }
	void setY(int tmp) { y = tmp; }			//setter and getter for Y
	int getY() { return y; }
	void setInput();						//setter and getter for inputString 
	char getChar1() { return char1; }
	char getChar2() { return char2; }
	int getInt1() { return int1; }
	int getInt2() { return int2; }
	void setType(int x) { type = x; }
	void setSquare1(Square *tmp) { first = tmp; }
	void setSquare2(Square *tmp) { second = tmp; }
	vector<Square*> getSquare1() { return first; }
	vector<Square*> getSquare2() { return second; }
	//copy constructor
	Line(const Line& p)
	{//copy all variables to this object
		on = p.on;
		owner = p.owner;
		x = p.x;
		y = p.y;
		char1 = p.char1;
		char2 = p.char2;
		int1 = p.int1;
		int2 = p.int2;
		type = p.type;
	}
	//overload = operator
	Line operator= (const Line& p)
	{
		//copy all variables to this object
		on = p.on;
		owner = p.owner;
		x = p.x;
		y = p.y;
		char1 = p.char1;
		char2 = p.char2;
		int1 = p.int1;
		int2 = p.int2;
		type = p.type;
		return p;
	}
};

