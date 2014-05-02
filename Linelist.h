#pragma once
#include "Line.h"
#include <string>
using namespace std;

class Linelist
{
	int type;		//0 = horizontal, 1 = vertical
	int x;			//first variable of Line array
	int y;			//second variable of Line array
	Line *next;
public:
	Linelist();
	~Linelist();
	Line getNext() { return *next; }
	Line setNext(Line x) { *next = x; }
	string getInput();
};

