#include "Game.h"

//public:

void Game::startGame()
{
	int first = randomBit();
	board.initBoard(first);

	if (endOfGame(WHITE))	//checks if AI has won
		return;
	if (endOfGame(BLACK))	//checks if the player has won 
		return;
	
	while (true)
	{
		if (first)
		{
			board.getBestMove(history);
			if (endOfGame(WHITE))	//checks if AI has won
				return;
			board.getPlayersMove(history);
			if (endOfGame(BLACK))	//checks if the player have won 
				return;
		}
		else
		{
			board.getPlayersMove(history);
			if (endOfGame(BLACK))		//checks if the player have won 
				return;
			board.getBestMove(history);
			if (endOfGame(WHITE))		//checks if AI has won
				return;
		}
	}
}

void Game::nextPlayerMove()
{
	board.printBoard();

	int x_coord;
	int y_coord;
	
	std::cout << "Enter x and y coord: ";
	std::cin >> x_coord;
	std::cin >> y_coord;
	std::cout << "\n";

	if (board.isEmpty(x_coord, y_coord))
		board.setMove(x_coord, y_coord, BLACK);
}

//private:

bool Game::endOfGame(Colour pl_col)
{
	if (board.finalState(pl_col))
	{
		if (pl_col == WHITE)
			std::cout << "You're defeated!\n";
		else
			std::cout << "You've won the game!\n";
	
		printGameHistory();
		return true;
	}
	return false;
}

int Game::randomBit()const
{
	return  rand() % 2;
}

void Game::printGameHistory()
{
	clearConsole();
	std::cout << "GAME HISTORY: " << std::endl;

	while (!history.empty())
	{
		history.front().print();
		history.pop();
	}
}