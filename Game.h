#ifndef __GAME__HEADER__INCLUDED__
#define __GAME__HEADER__INCLUDED__

#include "Board.h"

class Game
{
private:
	Board board;
	std::queue<State> history;
public:
	Game() = default;
public:
	void  startGame();
	void  nextPlayerMove();
private:
	bool endOfGame(Colour)const;
	int randomBit()const;
};

#endif