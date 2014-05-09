#pragma once
#include <string>
#include "Line.h"
#include "Square.h"
#include "Player.h"
#include <vector>
#include <list>
using namespace std;

class Data : Line, Square
{
	int amtPlayers;				//total amount of players
	Line hLine[7][8];			//used for horizontal line storage
	Line vLine[8][7];			//used for vertical line storage
	Square arrySqr[49];			//array of squares
	vector<Player*> playerList;	//list of players
	int whoseTurn;				//indicates whose turn in playerList it is
	char char1, char2;
	int int1, int2;
	int count;
	int gameLength;
public:
	Data(int);
	~Data();
	void applyMove(char,int,char,int);								//plays thru the game and refreshes gamescreen
	string getCurrentPlayer() { return playerList[whoseTurn]->getName(); }
	int getCurrentPlayerAI() { return playerList[whoseTurn]->getAI(); }
	int getWhoseTurn() { return whoseTurn; }
	void nextTurn() { whoseTurn++; if (whoseTurn == amtPlayers) whoseTurn = 0; }		//next Player's Turn
	bool checkEndGame();						//returns true if all squares have been captured
	bool endGame();								//endGame done here including displaying results and setting up next game
	void refreshGS();							//used in refresh() as the game screen refresher
	void populateList();						//populates list of lines left to be captured
	void initializePlayer(string, int);
	vector<Line*> getFreeLines();
	vector<Square*> getFreeSquares();
	void undoMove(Line *);
	int eval(int, int);

};