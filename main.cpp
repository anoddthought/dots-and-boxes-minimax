//main.cpp
//By: Jeremy Dobler
//Dots Program
//Header Information
#include <iostream>
#include <string>
#include "data.h"
#include "MinMax.h"

//included for resizing of windows
#define _WIN32_WINNT 0x0500
#include <Windows.h>

using namespace std;

void main()
{
	char char1, char2;			//initials input
	string initials;
	int type;					//type input
	//resizing window
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, 500, 480, TRUE);
	
	//Start new game
	Data game;

	//determine Player 1's type
	cout << "What type is player 1?\n 0: Player\n 1: MiniMax\n";
	cin >> type;

	switch (type)
	{
	case 0:
		cout << "Player 1's Initials: ";
		cin >> char1 >> char2;
		initials.push_back(char1);
		initials.push_back(char2);
		//initialize player objects with names
		game.initializePlayer(initials, type);
		break;
	case 1:
		cout << "Player 1 is Easy";
		game.initializePlayer("M1",type);
		break;
	}

	initials = "";
	//determine Player 2's type
	cout << "What type is player 2?\n 0: Player\n 1: MiniMax\n";
	cin >> type;

	switch (type)
	{
	case 0:
		cout << "Player 2's Initials: ";
		cin >> char1 >> char2;
		initials.push_back(char1);
		initials.push_back(char2);
		//initialize player objects with names
		game.initializePlayer(initials, type);
		break;
	case 1:
		cout << "Player 2 is MiniMax";
		game.initializePlayer("M1",type);
		break;
	}

	//play the game
	do{
		do
		{
			game.refresh();
			char c1, c2;
			int i1, i2;
			//get input from human or minimax algorithm
			if (game.getCurrentPlayerAI() == 0) //human player
			{
				//human player
				cout << endl << endl << "What is your next move(example a1a2 or A1B1): ";
				cin >> c1 >> i1 >> c2 >> i2;
			}
			else
			{
				char *minMaxMove;
				//minimax algorithm
				minMaxMove = game.MinMax();
				c1 = minMaxMove[0];
				i1 = minMaxMove[1];
				c2 = minMaxMove[2];
				i2 = minMaxMove[3];
			}
			game.giveMove(c1, i1, c2, i2);
			//repeat until checkEndGame
			
		}while(game.checkEndGame() == false);
	}while(game.endGame());

	//show the score and endgame result
	game.refreshGS();
	game.endGame();

	system("PAUSE");
}