//main.cpp
//By: Jeremy Dobler
//Dots Program
//Header Information
#include <iostream>
#include <string>
#include "data.h"

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
	cout << "What type is player 1?\n 0: Player\n 1: Random\n 2: Greedy\n";
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
		cout << "Player 1 is Random\n";
		game.initializePlayer("R1",type);
		break;
	case 2:
		cout << "Player 1 is Greedy\n";
		game.initializePlayer("G1", type);
		break;
	}

	initials = "";
	//determine Player 2's type
	cout << "What type is player 2?\n 0: Player\n 1: Random\n 2: Greedy\n";
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
		cout << "Player 2 is Random\n";
		game.initializePlayer("R2",type);
		break;
	case 2:
		cout << "Player 2 is Greedy\n";
		game.initializePlayer("G2", type);
		break;
	}
	//play the game
	do{
		do
		{
			game.refreshGS();
			//get games remaining lines
			vector<Line*> movesLeft = game.getFreeLines();
			//get game's free squares
			vector<Square*> squaresLeft = game.getFreeSquares();
			// generate a random number
			int random = rand() % movesLeft.size();
			//declaration of move variables
			char c1, c2;
			int i1, i2;
			//determine what input to get
			switch (game.getCurrentPlayerAI())
			{
			case 0: //human
			{
				cout << endl << endl << "What is your next move(example a1a2 or A1B1): ";
				cin >> c1 >> i1 >> c2 >> i2;
			}
				break;
			case 1: //random
			{
				//grab the input of random line
				c1 = movesLeft[random]->getChar1();
				i1 = movesLeft[random]->getInt1();
				c2 = movesLeft[random]->getChar2();
				i2 = movesLeft[random]->getInt2();
			}
			break;
			case 2: //greedy
			{
				//if square can be captured, grab it
				Line *tmp = movesLeft[random];
				for (vector<Square*>::iterator iter = squaresLeft.begin(); iter != squaresLeft.end(); iter++)
				{
					//if only one line left to capture, capture it
					if ((*iter)->linesLeftToCapture() == 1)
					{
						tmp = (*iter)->lineNotCaught();
						break;
					}
				}
				c1 = tmp->getChar1();
				i1 = tmp->getInt1();
				c2 = tmp->getChar2();
				i2 = tmp->getInt2();
				//if all line captures will lead to square capture on next turn, pick random move
			}
			break;
			case 3: //double-dealing
				//need function to check for chains
				//grab largest chain and iterate through it
				//if currentChain is NULL, grab new chain else random line
				//with 3 lines left to capture in chain
				//grab last line, leaving middle 2 lines for capture
				break;
			}
			//END OF Switch

			game.applyMove(c1, i1, c2, i2);
			//repeat until checkEndGame
			
		}while(game.checkEndGame() == false);
	}while(game.endGame());

	//show the score and endgame result
	game.refreshGS();
	game.endGame();

	system("PAUSE");
}