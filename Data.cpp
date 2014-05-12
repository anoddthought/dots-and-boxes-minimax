//data.cpp
//Dots Game
//By:Jeremy Dobler
//Holds Data, Line, Square Classes
//Data holds control of game
//Line and square classes are used by Data in arrays
//Header information
#include <iostream>
#include <iomanip>
#include <string>
#include "data.h"
#include "Player.h"
#include <list>
#include "Line.h"
using namespace std;

Data::Data()
{
	//initialize whoseTurn and amount of Players to 0
	whoseTurn = 0; 
	amtPlayers = 0;
	count = 0;
	
	//TODO populate freeLineList and freeSquareList
	populateList();

}

//Data member functions
//handles next pointer cases and initializes new Player with name given by user
void Data::initializePlayer(string n, int x)
{
	//create player object
	Player *temp = new Player();
	//set player name
	temp->setName(n);
	//set player ai
	temp->setAI(x);
	//add Player to list of players
	playerList.push_back(temp);
	//go to next player
	amtPlayers++;
}

//checks if user would like to play again
bool Data::endGame()
{
	//increment total game score for person with highest score
	if (playerList[0]->getGameScore() > playerList[1]->getGameScore())
	{
		playerList[0]->incrementTotalScore();
	}
	else
		playerList[1]->incrementTotalScore();
	refreshGS();
	//input variable
	char cont = ' ';
	while (cont != 'y' && cont != 'n')
	{
		cout << "\nWould you like to continue playing \nwith same players?(y for yes, n for no)";
		if (count != 100)
		{
			cont = 'y';
		}
		else
		{
			cin >> cont;
		}
		count++;
		cout << "\nI do not understand your input.";
	}
	if (cont == 'n')
		return true;	//tell user to endGame
	else
	{
		//user wants to keep playing reset gameScore and whoseTurn
		for (int x = 0; x < amtPlayers; x++)
		{
			playerList[x]->resetGameScore();
		}
		//set turn back to original
		whoseTurn = 0;

		//reset all square
		for (int x = 0; x < 49; x++)
			arrySqr[x].reset();
		//reset all line objects
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				hLine[x][y].reset();	//hLine[7][8]
				vLine[y][x].reset();	//x and y switched for vLine[8][7]
			}
		}
		populateList();		//repopulate freeLineList with all the lines
		return false;		//returns false for do not end the game
	}
}

//refresh the Game Screen with the gameboard and scoreboard
void Data::refreshGS()
{
	//display whose Turn it is
	cout << playerList[whoseTurn]->getName() << ", it is your turn." << endl;

	int sqrCount = 0;		//count for Square array
	char leftcol = 'A';		//used to output current row A-H

	cout << "   1    2    3    4    5    6    7    8" << endl;
	//prints dots 2-8 and any horizontal lines in this row
	for (int y = 0; y < 7; y++)
	{
		cout << leftcol << "  o";	//display column identifier with first dot
		leftcol += 1;				//increment column identifier

		//displays one row with horizontal lines
		for (int x = 0; x < 7; x++)
		{
			hLine[x][y].hdisplay();
			cout << 'o';
		}
		cout << endl;
		//displays all rows with vertical lines
		//display top row with possibly ownership
		cout << "   ";
		for (int x = 0; x < 7; x++)
		{
			vLine[x][y].vdisplay();
			arrySqr[sqrCount].display();
			sqrCount++;
		}
		//displays last vertical lines
		vLine[7][y].vdisplay();
		//next row
		cout << endl;

		//print row 2 without owner display
		cout << "   ";
		for (int x = 0; x < 7; x++)
		{
			vLine[x][y].vdisplay();
			cout << "    ";
		}
		//displays last vertical lines
		vLine[7][y].vdisplay();
		//next row
		cout << endl;

	}
	//print row I of grid
	cout << leftcol << "  o";	//display column identifier with first dot
	//displays one row with horizontal lines
	for (int x = 0; x < 7; x++)
	{
		hLine[x][7].hdisplay();
		cout << 'o';
	}
	cout << endl << endl << endl;

	cout << " Player     Game Score     Total Wins " << endl;
	//display Player names and scores
	for (int count = 0; count < amtPlayers; count++)
	{
		cout << "   " << playerList[count]->getName() << "       " << setw(10) << playerList[count]->getGameScore()
			<< "     " << setw(10) << playerList[count]->getTotalScore() << endl;
	}
	////END DISPLAY OF GAME BOARD////
}

//update game screen to standard game screen with gameboard at top and user input at bottom
//will increment whoseTurn to next Player if user captures a line
void Data::refresh()
{
	//if both chars are between A&H and both ints are between 1&8 then input is ok
	if ((char1 >= 65 && char1 <= 72) && (char2 >= 65 && char2 <= 72)
		&& (int1 >= 1 && int1 <= 8) && (int2 >= 1 && int2 <= 8))
	{
		int x, y;
		///HORIZONTAL LINE CAPTURE CHECK///
		if (char1 == char2)
		{
			int temp = int2 - int1;
			//chars are equal so there must be a difference of 1 between ints
			if (temp == 1 || temp == -1)
			{
				//chars are equal so it doesn't matter which one is subtracted
				y = char1 - 65;
				//must take -1 from smaller int to get array address
				if (int2 > int1)
					x = int1 - 1;
				else
					x = int2 - 1;
				if (hLine[x][y].getOn() == false)	//checks to see if line is captured
				{
					//capture horizontal line
					hLine[x][y].capture(playerList[whoseTurn]->getName());
					//figure out square Numbers associated with line captured
					int bottomSqr = y * 7 + x;
					int topSqr = bottomSqr - 7;
					bool test1 = false, test2 = false;
					//test top and bottom square to see if player completed the square
					//don't test1 if we are on the top row of hLine
					if (y != 0)
						test1 = arrySqr[topSqr].capture(playerList[whoseTurn]->getName(), topSqr, hLine, vLine);
					if (y != 7)
						test2 = arrySqr[bottomSqr].capture(playerList[whoseTurn]->getName(), bottomSqr, hLine, vLine);
					if (test1 || test2)
					{
						//player captured a square do not advance to next turn and increment player's gamescore
						//need to determine if player captured one or two squares with the one line
						if (test1)
						{
							playerList[whoseTurn]->incrementGameScore();
						}
						if (test2)
						{
							playerList[whoseTurn]->incrementGameScore();
						}
					}
					else
						nextTurn();
				}
				else
					cout << "Line already captured. Try again. " << endl;
			}
			else
			{
				cout << "\nThe dots are not immediately next to each other. \nPlease try again.";
			}

		}
		///VERTICAL LINE CAPTURE CHECK///
		else if (int1 == int2)
		{
			//ints are equal, check for difference of 1 between chars
			int temp = char2 - char1;
			if (temp == 1 || temp == -1)
			{
				x = int1 - 1;
				if (char1 > char2)
					y = char2 - 65;
				else
					y = char1 - 65;
				if (vLine[x][y].getOn() == false)
				{
					//capture vertical line
					vLine[x][y].capture(playerList[whoseTurn]->getName());
					//determine square number to left and right of vertical line	
					int rightSqr = y * 7 + x;
					int leftSqr = rightSqr - 1;
					bool test1 = false, test2 = false;
					//test top and bottom square to see if player completed the square
					if (x != 7)	// do not test for right square if vLine is most right line
						test1 = arrySqr[rightSqr].capture(playerList[whoseTurn]->getName(), rightSqr, hLine, vLine);
					if (x != 0) // do not test for left square if vLine is most left line
						test2 = arrySqr[leftSqr].capture(playerList[whoseTurn]->getName(), leftSqr, hLine, vLine);
					if (test1 || test2)
					{
						//player captured a square do not advance to next turn and increment player's gamescore
						//need to determine if player captured one or two squares with the one line
						if (test1)
							playerList[whoseTurn]->incrementGameScore();
						if (test2)
							playerList[whoseTurn]->incrementGameScore();
					}
					else
						nextTurn();
				}
				else
					cout << "Line already captured. Try again. " << endl;
			}
			else
			{
				cout << "\nThe dots are not immediately next to each other. \nPlease try again.";
			}
		}
		else
			cout << "\n The dots are not immediately next to each other. \nPlease try again. ";
	}
	////End check for line and square captures
	///////check for endGame()////////
	if (checkEndGame())
		endGame();
	//else continue game
	//refresh game screen
	refreshGS();
}

//Checks to see if all squares are on and returns true
bool Data::checkEndGame()
{
	for (int count = 0; count < 49; count++)
	{
		//check to see if Square is on
		if (!arrySqr[count].getOn())
		{
			//if it is not on return false and continue game
			return false;
		}
	}
	return true;
}

//Populate free list
void Data::populateList()
{
	//add horizontal lines
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			//initialize attributes 
			hLine[x][y].setX(x);
			hLine[x][y].setY(y);
			hLine[x][y].setType(0);
			hLine[x][y].setInput();
		}
	}
	//add vertical lines
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			//initialize attributes
			vLine[x][y].setX(x);
			vLine[x][y].setY(y);
			vLine[x][y].setType(1);
			vLine[x][y].setInput();
		}
	}
	//populate square list with all squares
	//initialize square object with pointers to lines that make it up
	for (int x = 0; x < 49; x++)
	{
		Line *top = &hLine[x % 7][x / 7];
		Line *bottom = &hLine[x % 7][x / 7 + 1];
		Line *left = &vLine[x % 7][x / 7];
		Line *right = &vLine[(x % 7) + 1][x / 7];
		arrySqr[x].setLines(left, right, top, bottom);
		arrySqr[x].setPosition(x);
	}

}

vector<Line*> Data::getBestChain()
{
	//stores the best chain to get
	//holds lines in order from first to last
	vector<Line*> bestChain;
	vector<Line*> nextChain;

	vector<Square*> freeSquares = getFreeSquares();
	//iterate through all free squares
	//check lines that connect the square to the other squares
	for (vector<Square*>::iterator iter = freeSquares.begin(); iter != freeSquares.end(); ++iter)
	{
		nextChain.clear();
		int x = (*iter)->getPosition();
		//if square can be captured, get all lines that are part of its chain
		if ((*iter)->linesLeftToCapture() == 1)
		{
			vector<Line*>::iterator currentLine = nextChain.begin();
			while (currentLine != nextChain.end())
			{
				nextChain.push_back((*iter)->linesNotCaught()[0]);
				//check the squares that are next to this square
				int squares[4];
				if ((x % 7) != 0)
				{
					//left Square is valid
					squares[0] = x - 1;
				}
				if ((x % 7) != 1)
				{
					//right square is valid
					squares[1] = x + 1;
				}
				if (x < 42)
				{
					//bottom square is valid
					squares[2] = x + 7;
				}
				if (x > 6)
				{
					//top square is valid
					squares[4] = x - 7;
				}

				//iterate through the four surrounding squares checking for the currentLine
				for (int x = 0; x < 4; x++)
				{
					//check which square also contains the line we might captured
					if (squares[x] != NULL)
					{
						//this square contains the line
						if (arrySqr[squares[x]].containsLine((*currentLine)))
						{
							//check to see if we continue the search
							//or if the next square can be captured after we capture the previous line
							if (arrySqr[squares[x]].linesLeftToCapture() == 2)
							{
								//get next line to check in the loop
								vector<Line*> linesLeft = arrySqr[squares[x]].linesNotCaught();
								if (linesLeft[0] != (*currentLine))
									nextChain.push_back(linesLeft[0]);
								else if (linesLeft[1] != (*currentLine))
									nextChain.push_back(linesLeft[1]);
								break;
							}
						}
					}
				}
				currentLine++;
			}
		}
		//check the chain we just created
		if (nextChain.size() > bestChain.size())
		{
			bestChain.clear();
			bestChain = nextChain;
		}
	}
	return bestChain;
}

vector<Line*> Data::getFreeLines()
{
	vector<Line*> freeLineList;
	//add horizontal lines
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (!hLine[x][y].getOn())
				//add Line item to free list
				freeLineList.push_back(&hLine[x][y]);
		}
	}
	//add vertical lines
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			if (!vLine[x][y].getOn())
				//add Line item to free list
				freeLineList.push_back(&vLine[x][y]);
		}
	}
	return freeLineList;
}

vector<Square*> Data::getFreeSquares()
{
	vector<Square*> freeSquareList;
	//populate square list with all squares
	//initialize square object with pointers to lines that make it up
	for (int x = 0; x < 49; x++)
	{
		Line *top = &hLine[x % 7][x / 7];
		Line *bottom = &hLine[x % 7][x / 7 + 1];
		Line *left = &vLine[x % 7][x / 7];
		Line *right = &vLine[(x % 7) + 1][x / 7];
		arrySqr[x].setLines(left, right, top, bottom);
		freeSquareList.push_back(&arrySqr[x]);
	}
	return freeSquareList;
}

vector<Line*> Data::getSecondLines()
{
	vector<Square*> freeSquares = getFreeSquares();
	vector<Line*> bestSecondLines;
	//iterate through all free squares and grab lines that have not been completed
	for (vector<Square*>::iterator iter = freeSquares.begin(); iter != freeSquares.end(); ++iter)
	{
		if ((*iter)->linesLeftToCapture() > 2)
		{
			//get the lines that can be caught in this square
			vector<Line*> tmp = (*iter)->linesNotCaught();

			//iterate through lines and make sure they will not complete the other square
			for (vector<Line*>::iterator iter = tmp.end(); iter != tmp.begin();--iter)
			{
				if ( (arrySqr[(*iter)->getSquare1()].linesLeftToCapture() == 2) || (arrySqr[(*iter)->getSquare2()].linesLeftToCapture == 2) )
				{
					//if the line will create a capturable square
					//delete it from the vector
					tmp.erase(iter);
				}
			}
		}
	}

	return bestSecondLines;
}