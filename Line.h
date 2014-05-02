#pragma once
#include <string>
using namespace std;

class Line
{
	bool on;								//false for off, true for on
	string owner;							//contains owner's name
	int x, y;								//line coordinates
	char* input;
	int type;								//0 = horizontal, 1 = vertical
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
	char* getInput() { return input; };
	void setType(int x) { type = x; }
	//copy constructor
	Line(const Line& p)
	{//copy all variables to this object
		on = p.on;
		owner = p.owner;
		x = p.x;
		y = p.y;
		input = p.input;
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
		input = p.input;
		type = p.type;
		return p;
	}
};

