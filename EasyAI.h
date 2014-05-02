#pragma once
#include <iostream>
#include "Player.h"
#include <vector>
#include "Line.h"
using namespace std;

class EasyAI : public Player
{
public:
	string name;			//2 character name of player
	string nextMove;		//4 character string holding the next move
	int total_score;		//total amount of games the player has won
	int game_score;			//score of the game being played currently

public:
	~EasyAI() {};
	//functions handling game_score
	void resetGameScore() { game_score = 0; }
	void incrementGameScore() { game_score++; }
	int getGameScore() { return game_score; }

	//functions handling total_score
	void resetAll() { total_score = 0; game_score = 0; }		//resets both scores
	void incrementTotalScore() { total_score++; }				//increment player's total_score
	int getTotalScore() { return total_score; }

	//functions handling name
	void setName(string n) { name = n; }
	string getName() { return name; }

	//function to determine the next move, modified in child classes for each type of player
	virtual string getMove(vector<Line*>);
	virtual string getMove() override;

	//constructor no-arg
	EasyAI() { game_score = 0; total_score = 0; }

	//copy constructor
	EasyAI(const EasyAI& p)
	{//copy all variables to this object
		name = p.name;
		total_score = p.total_score;
		game_score = p.game_score;
	}
	//overload = operator
	EasyAI operator= (const EasyAI& p)
	{
		//copy all variables to this object
		name = p.name;
		total_score = p.total_score;
		game_score = p.game_score;
	}
};