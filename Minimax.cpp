#include "Minimax.h"

Minimax::Minimax()
{
}


Minimax::~Minimax()
{
}

Line* Minimax::mini_max(Data *game, int cutoff)
{
	maxPlayer = game->getWhoseTurn();
	if (maxPlayer == 0)
		minPlayer = 1;
	else minPlayer = 0;
	int alpha = -9999;
	int beta = 9999;

	minimaxmove bestMove = max(game, cutoff, alpha, beta, true);
	return bestMove.move;
}

minimaxmove Minimax::max(Data *game, int cutoffForTurns,int alpha, int beta, bool toplevel)
{
	vector<Line*> bestMoves;
	//get remaining moves
	vector<Line*> moves = game->getFreeLines();
	//initialize bestVal to really low number
	minimaxmove nextMove;
	//check to see if game is over or no moves remain
	if (game->checkEndGame() || cutoffForTurns == 0)
	{
		moves.clear();
		nextMove.value = game->eval(maxPlayer, minPlayer);
		return nextMove;
	}

	//iterate through each move and get the best_move or max move
	for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
	{
		//do the move
		game->applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());
		//check to see if it is still maxPlayer's turn
		if (game->getWhoseTurn() == maxPlayer)
			nextMove = max(game, cutoffForTurns-1, alpha, beta, false);
		else //mins turn
			nextMove = min(game, (cutoffForTurns-1), alpha, beta);
		//check to see which move is better, nextMove or bestMove
		//check for alpha move
		if (nextMove.value > alpha)
		{
			alpha = nextMove.value;
			if (toplevel)
			{
				//empty the bestMoves vector since the current move is better than all of the previous best moves
				bestMoves.clear();
				bestMoves.push_back(*iter);
			}
		}
		else if (toplevel && nextMove.value == alpha)
		{
			//add the current move to the vector of bestmoves
			bestMoves.push_back(*iter);
		}
		//done with this move, undo it so we can check the next one
		game->undoMove((*iter));
		//alpha beta pruning done here
		if (beta <= alpha)
		{
			moves.clear();
			//iterate through bestMoves and choose one
			//now the best moves are stored in bestMoves
			//randomly pick a best move from the vector
			if (toplevel)
			{
				int random = rand() % bestMoves.size();
				nextMove.move = bestMoves[random];
				bestMoves.clear();
			}

			nextMove.value = alpha;
			return nextMove;
		}
	}
	moves.clear();
	//now the best moves are stored in bestMoves
	//randomly pick a best move from the vector
	if (toplevel)
	{
		int random = rand() % bestMoves.size();
		nextMove.move = bestMoves[random];
		bestMoves.clear();
	}
	nextMove.value = alpha;
	return nextMove;
}

minimaxmove Minimax::min(Data *game, int cutoffForTurns, int alpha, int beta)
{
	//get remaining moves
	vector<Line*> moves = game->getFreeLines();
	minimaxmove nextMove;
	//check to see if game is over or no moves remain
	if (game->checkEndGame() || cutoffForTurns == 0)
	{
		moves.clear();
		nextMove.value = game->eval(maxPlayer, minPlayer);
		return nextMove;
	}

	//iterate through each move and get the best_move or max move
	for (vector<Line*>::iterator iter = moves.begin(); iter != moves.end(); ++iter)
	{
		//do the move
		game->applyMove((*iter)->getChar1(), (*iter)->getInt1(), (*iter)->getChar2(), (*iter)->getInt2());
		//check to see if it is still minPlayer's turn
		if (game->getWhoseTurn() == minPlayer)
			nextMove = min(game, cutoffForTurns-1, alpha, beta);
		else //mins turn
			nextMove = max(game, cutoffForTurns-1, alpha, beta, false);
		//check to see which move is better, nextMove or bestMove
		if (nextMove.value < beta)
		{
			beta = nextMove.value;
		}
		//done with this move, undo it so we can check the next one
		game->undoMove((*iter));
		//alpha beta pruning done here
		if (beta <= alpha)
		{
			moves.clear();
			nextMove.value = beta;
			return nextMove;
		}
	}
	moves.clear();
	nextMove.value = beta;
	return nextMove;
}