#include "Minimax.h"


Minimax::Minimax()
{
}


Minimax::~Minimax()
{
}

Line* Minimax::mini_max(Data *game, int cutoff)
{
	int cutoffForMe = 5;
	vector<Line*> moves;
	vector<Line*> bestMoves;
	moves = game->getFreeLines();
	char result[4];
	//get the current players turn to test if I captured a square during each move
	maxPlayer = game->getWhoseTurn();
	if (maxPlayer == 0)
		minPlayer = 1;
	else minPlayer = 0;
	//stores values to determine the best move
	int nextVal;
	int bestVal = -999999;
	int alpha = -9999999;
	int beta = 9999999;
	//bestMove stores the line that should be taken next
	Line *bestMove;

	//iterator through each move and get the best_move or max move
	for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
	{
		//do the move
		game->applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());

		//check to see if it is still maxPlayer's turn
		if (game->getWhoseTurn() == maxPlayer)
			//current player is the same, get max value
			nextVal = max(game, cutoff, alpha, beta);
		else //mins turn
			nextVal = min(game, cutoff, alpha, beta);
		//check to see which move is better, nextMove or bestMove
		if (nextVal > bestVal)
		{
			//empty the bestMoves vector since the current move is better than all of the previous best moves
			bestMoves.clear();
			bestVal = nextVal;
			bestMoves.push_back(*iter);
		}
		else if (nextVal == bestVal)
		{
			//add the current move to the vector of bestmoves
			bestMoves.push_back(*iter);
		}
		//done with this move, undo it so we can check the next one
		game->undoMove((*iter));
		//check for alpha move
		if (bestVal > alpha)
		{
			alpha = bestVal;
		}
	}

	//now the best moves are stored in bestMoves
	//randomly pick a best move from the vector
	int random = rand() % bestMoves.size();
	bestMove = bestMoves[random];
	return bestMove;
}

int Minimax::max(Data *game, int cutoffForTurns,int alpha, int beta)
{
	//get remaining moves
	vector<Line*> moves = game->getFreeLines();
	//initialize bestVal to really low number
	int bestVal = -999999;
	int nextVal;
	//check to see if game is over or no moves remain
	if (game->checkEndGame() || cutoffForTurns == 0)
		return (game->eval(maxPlayer, minPlayer));

	//iterate through each move and get the best_move or max move
	for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
	{
		//do the move
		game->applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());

		//check to see if it is still maxPlayer's turn
		if (game->getWhoseTurn() == maxPlayer)
			nextVal = max(game, cutoffForTurns, alpha, beta);
		else //mins turn
			nextVal = min(game, cutoffForTurns-1, alpha, beta);
		//check to see which move is better, nextMove or bestMove
		if (nextVal > bestVal)
		{
			bestVal = nextVal;
		}
		//done with this move, undo it so we can check the next one
		game->undoMove((*iter));
		//check for alpha move
		if (bestVal > alpha)
		{
			alpha = bestVal;
		}
		//alpha beta pruning done here
		if (bestVal >= beta)
		{
			return bestVal;
		}
	}
	return bestVal;
}

int Minimax::min(Data *game, int cutoffForTurns, int alpha, int beta)
{
	//get remaining moves
	vector<Line*> moves = game->getFreeLines();
	//initialize worstVal to really high number
	int worstVal = 999999;
	int nextVal;
	//check to see if game is over or no moves remain
	if (game->checkEndGame() || cutoffForTurns == 0)
		return (game->eval(maxPlayer, minPlayer));

	//iterate through each move and get the best_move or max move
	for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
	{
		//do the move
		game->applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());

		//check to see if it is still minPlayer's turn
		if (game->getWhoseTurn() == minPlayer)
			nextVal = min(game, cutoffForTurns, alpha, beta);
		else //mins turn
			nextVal = max(game, cutoffForTurns-1, alpha, beta);
		//check to see which move is better, nextMove or bestMove
		if (nextVal < worstVal)
		{
			worstVal = nextVal;
		}
		//done with this move, undo it so we can check the next one
		game->undoMove((*iter));
		//check for beta value
		if (worstVal < beta)
		{
			beta = worstVal;
		}
		//alpha beta pruning done here
		if (worstVal <= alpha)
		{
			return worstVal;
		}
	}
	return worstVal;
}