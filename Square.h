#pragma once
#include <string>
#include "Line.h"
using namespace std;
//same values must be in Data
#define XGRID 4
#define YGRID 4

class Square
{
	bool on;
	string owner;
	Line *left, *right, *top, *bottom;			//pointers to the lines that make up the square
public:
	Square() { on = false, owner = "  "; }		//no-arg constructor, sets all to default values off and ""
	~Square();
	void display();								//display initials of owner of square
	void reset() { on = false; owner = "  "; }	//reset all variables	
	bool capture(string, int, Line[XGRID][YGRID+1], Line[XGRID+1][YGRID]);		//check to see if all lines that make up the square are all on or not
	bool getOn() { return on; }					//returns bool on to see if square is on
	string getOwner() { return owner; }			//return string owner
	void setLines(Line*, Line*, Line*, Line*);
	int linesLeftToCapture();
	Line* lineNotCaught();
	bool lineIsInSquare(Line*);
};

