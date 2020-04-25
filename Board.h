#ifndef __BOARD__HEADER__INCLUDED__
#define __BOARD__HEADER__INCLUDED__

#include <vector>
#include <queue>
#include <algorithm>

#include "Interface_functions.h"
#include "Heuristic_function.h"

const int MIN_INF = -1000;
const int PLUS_INF = 1000;
const unsigned MAX_DEPTH = 3;

const char WHITE_SQUARE = 0xDB;
const char BLACK_SQUARE = 0xFF;

typedef std::vector<Coordinates> POSSIBLE_MOVES_GRAPHS[3][3];

struct State
{
	BOARD board;

	void print()
	{
		for (size_t row = 0; row < MAX_SIZE; ++row)
		{
			for (size_t col = 0; col < MAX_SIZE; ++col)
		
			{
				std::cout << board[row][col].symbol;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

class Board
{
public:
	BOARD rota_board;
	POSSIBLE_MOVES_GRAPHS moves;

public:
	Board();
public:
	void getBestMove(std::queue<State>& history);
	void getPlayersMove(std::queue<State>& history);

	void initBoard(size_t);
	void printBoard()const;

	bool finalState(Colour)const;
	bool isEmpty(int, int)const;

	void setMove(int, int, Colour);

private:
	int miniMax(State,size_t, bool, int, int);

	void initAI();
	void initPlayer();

	void printRow(size_t)const;
	void printSemiRow(size_t, char)const;
	void initMoveGraph();
	void pushPossibleMoves(size_t, size_t);
	void copyCurrBoard(State&)const;
	void copyPrevState(const State&, State&);
	void addBoardConfiguration(std::queue<State>& history)const;

	bool threeInLine(Colour)const;
	bool threeInDiagonal(Colour)const;
	bool threeOnEdge(Colour)const;
	bool isAdjecentCell(size_t, size_t, size_t, size_t)const;
	bool boardEmpty()const;
};

#endif