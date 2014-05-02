#include "Line.h"
#include <iostream>
#include <string>

Line::~Line()
{
}

//Line Member Functions
//only use this display function when displaying a horizontal line
void Line::hdisplay()
{
	if (on == true)
		cout << "----";
	else
		cout << "    ";
}

//only use the display function when displaying vertical lines
void Line::vdisplay()
{
	if (on == true)
		cout << "|";
	else
		cout << " ";
}

//will return false if line not captured
bool Line::capture(string name)
{
	if (on == true)
	{
		cout << "Line already captured by " << owner << endl;
		return false;
	}
	else
	{
		on = true;
		owner = name;
		return true;
	}
}

//determine what the input string is (example: a1a2 for hLine[0][0])
void Line::setInput()
{
	input = "";
	char char1, char2;
	int int1, int2;
	//if horizontal, chars are equal
	if (type == 0)
	{
		//chars are equal so add 65 to create char ascii
		char1 = y + 65;
		char2 = char1;
		//add 1 to x array address to get smaller int, add 2 for larger int
		int1 = x + 1;
		int2 = x + 2;
	}
	//else if vertical, ints are equal
	else
	{
		//add one to x array address for the int values
		int1 = x + 1;
		int2 = int1;
		//add 65 to y array address to get lower letter in ascii form
		char1 = y + 65;
		char2 = char1 + 1;
	}
	
	input[0] = char1;
	input[1] = int1;
	input[2] = char2;
	input[3] = int2;
}
