//main.cpp
//By: Jeremy Dobler
//Dots Program
//Header Information
#include <iostream>
#include <string>
#include <time.h>
#include "data.h"

//included for resizing of windows
#define _WIN32_WINNT 0x0500
#include <Windows.h>

using namespace std;
int alphabeta(Data*, int, int, int, int, int, int);
void main()
{
	list<clock_t> minimaxtimetaken;
	list<clock_t> randomtimetaken;
	list<clock_t> greedytimetaken;
	char char1, char2;			//initials input
	string initials;
	int type;					//type input
	int amtOfGames;
	//resizing window
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, 580, 460, TRUE);

	//determine how many games to play
	cout << "How many games: ";
	cin >> amtOfGames;

	//Start new game
	Data game(amtOfGames);


	//determine Player 1's type
	cout << "What type is player 1?\n 0: Player\n 1: Random\n 2: Greedy\n 3: Minimax\n";
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
	case 3:
		cout << "Player 1 is Minimax\n";
		game.initializePlayer("M1", type);
		break;
	}

	initials = "";
	//determine Player 2's type
	cout << "What type is player 2?\n 0: Player\n 1: Random\n 2: Greedy\n 3: Minimax\n";
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
	case 3:
		cout << "Player 2 is Minimax\n";
		game.initializePlayer("M2", type);
		break;
	}
	game.refreshGS();
	//play the game
	do{
		do
		{
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
				//get time and add to array
				clock_t start = clock();
				//grab the input of random line
				c1 = movesLeft[random]->getChar1();
				i1 = movesLeft[random]->getInt1();
				c2 = movesLeft[random]->getChar2();
				i2 = movesLeft[random]->getInt2();
				randomtimetaken.push_back(clock() - start);
			}
			break;
			case 2: //greedy
			{
				//get time and add to array
				clock_t start = clock();
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
				greedytimetaken.push_back(clock() - start);
				c1 = tmp->getChar1();
				i1 = tmp->getInt1();
				c2 = tmp->getChar2();
				i2 = tmp->getInt2();
				//if all line captures will lead to square capture on next turn, pick random move
			}
			break;
			case 3: //Minimax
				//get time and add to array
				clock_t start = clock();
				//alphabeta search done here
				vector<Line*> moves = game.getFreeLines();
				vector<Line*> bestMoves;
				int minPlyr;
				int maxPlyr = game.getWhoseTurn();
				if (maxPlyr == 0)
					minPlyr = 1;
				else minPlyr = 0;
				int depth = 6;
				int nextdepth;
				int alpha = -9999;
				int beta = 9999;
				for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
				{
					game.applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());
					/*if (game.getWhoseTurn() != maxPlyr)
					{
						//min player's turn, decrement depth
						nextdepth = depth - 1;

					}
					else nextdepth = depth;*/
					int tmp = alphabeta(&game, depth-1, alpha, beta, maxPlyr, minPlyr, game.getWhoseTurn());
					if (tmp > alpha)
					{
						bestMoves.clear();
						bestMoves.push_back((*iter));
						alpha = tmp;
					}
					else if (tmp == alpha)
					{
						bestMoves.push_back((*iter));
					}
					game.undoMove((*iter));
				}
				//pick random move out of bestmoves
				int random = rand() % bestMoves.size();
				Line* bestMove = bestMoves[random];
				//end alphabeta search
				minimaxtimetaken.push_back(clock() - start);
				c1 = bestMove->getChar1();
				i1 = bestMove->getInt1();
				c2 = bestMove->getChar2();
				i2 = bestMove->getInt2();
				break;
			}
			//END OF Switch

			cout << game.getCurrentPlayer() << "'s Move: " << c1 << i1 << c2 << i2 << endl;
			game.applyMove(c1, i1, c2, i2);
			//repeat until checkEndGame
			game.refreshGS();
			if (game.checkEndGame())
				game.endGame();
		}while(game.checkEndGame() == false);
	}while(game.endGame());

	float totaltime = 0;
	//show how long greedy took
	for (list<clock_t>::iterator iter = greedytimetaken.begin(); iter != greedytimetaken.end(); ++iter)
	{
		totaltime += (*iter);
	}
	if (totaltime != 0)
	{
		float avgtime = totaltime / greedytimetaken.size();
		cout << "Greedy Time Taken: " << avgtime << " milliseconds" << endl;
	}

	totaltime = 0;
	//show how long minimax took
	for (list<clock_t>::iterator iter = minimaxtimetaken.begin(); iter != minimaxtimetaken.end(); ++iter)
	{
		totaltime += (*iter);
	}
	if (totaltime != 0)
	{
		float avgtime = totaltime / minimaxtimetaken.size();
		cout << "Minimax Time Taken: " << avgtime << " milliseconds" << endl;
	}

	system("PAUSE");
}

int alphabeta(Data* node, int depth, int alpha, int beta, int maxPlayer, int minPlayer, int previousTurn)
{
	int nextdepth = depth;
	if (depth == 0 || node->checkEndGame())
	{
		int result = node->eval(maxPlayer, minPlayer);
		return result;
	}
	vector<Line*> moves = node->getFreeLines();
	if (node->getWhoseTurn() == maxPlayer)
	{
		for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
		{
			node->applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());
			/*if (previousTurn == minPlayer)
			{
				//last turn was maxPlayer, this turn is minPlayer, decrement depth
				nextdepth = depth - 1;

			}*/
			int tmp = alphabeta(node, depth-1, alpha, beta, maxPlayer, minPlayer, maxPlayer);
			if (tmp > alpha)
			{
				alpha = tmp;
			}
			node->undoMove((*iter));
			if (beta <= tmp)
			{
				return tmp;
			}
		}
		return alpha;
	}
	else //min's turn
	{
		for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
		{
			node->applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());
			/*if (previousTurn == maxPlayer)
			{
				nextdepth = depth - 1;
			}*/
			int tmp = alphabeta(node, depth-1, alpha, beta, maxPlayer, minPlayer, minPlayer);
			if (tmp < beta)
			{
				beta = tmp;
			}
			node->undoMove((*iter));
			if (tmp <= alpha)
			{
				return tmp;
			}
		}
		return beta;
	}
}