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
	vector<Line*> freelist;		//list of Lines that have not been captured
	char char1, char2;
	int int1, int2;
public:
	Data();
	~Data() {};
	void refresh();								//plays thru the game and refreshes gamescreen
	string getCurrentPlayer() { return playerList[whoseTurn]->getName(); }
	int getCurrentPlayerAI() { return playerList[whoseTurn]->getAI(); }
	void nextTurn() { whoseTurn++; if (whoseTurn == amtPlayers) whoseTurn = 0; }		//next Player's Turn
	bool checkEndGame();						//returns true if all squares have been captured
	bool endGame();								//endGame done here including displaying results and setting up next game
	void refreshGS();							//used in refresh() as the game screen refresher
	void populateList();						//populates list of lines left to be captured
	void giveMove(char c1, int i1, char c2, int i2) 
	{ 
		char1 = toupper(c1); int1 = i1; char2 = toupper(c2); int2 = i2; 
	}
	void initializePlayer(string, int);

	//methods used for minimax
	char* MinMax();
	Line MaxMove(Data);
	Line MinMove(Data);
	int getPlayer() { return whoseTurn; }
	vector<Line**> getRemainingLines() { return freelist; }
	int addLine(Line line);
	Data clone();
	Line evalGameState() { Line tmp = freelist.front(); return tmp; }
	Data applyMove(Line);
};

