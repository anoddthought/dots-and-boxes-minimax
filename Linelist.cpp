#include "Linelist.h"


Linelist::Linelist()
{
}


Linelist::~Linelist()
{
}

string Linelist::getInput()
{
	char char1, char2, int1, int2;
	string input = "";
	//if horizontal, chars are equal
	if (type == 0)
	{
		//chars are equal so add 65 to create char ascii
		char1 = y + 65;
		char2 = char1;
		//add 1 to x array address to get smaller int, add 2 for larger int
		int1 = x + 1;
		int2 = x + 2;
		input = char1 + int1 + char2 + int2;
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
		input = char1 + int1 + char2 + int2;
	}
	return input;
}