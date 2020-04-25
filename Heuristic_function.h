#ifndef __HEUTISTIC_FUNCTION__HEADER__INCLUDED__
#define __HEUTISTIC_FUNCTION__INCLUDED__

const size_t MAX_SIZE = 3;

enum Colour
{
	EMPTY = 0,
	WHITE,
	BLACK
};

struct Coordinates
{
	int x_coord;
	int y_coord;

	Coordinates(int x_coord = -1, int y_coord = -1):
		x_coord(x_coord),
		y_coord(y_coord)
	{}

	bool operator==(const Coordinates& other)
	{
		return x_coord == other.x_coord && y_coord == other.y_coord;
	}
};



struct Position
{
	Colour colour;
	char symbol;

	Position(Colour colour = EMPTY, char symbol = ' '):
		colour(colour),
		symbol(symbol)
	{}

	void setCell(Colour col)
	{
		if (col == WHITE)
		{
			colour = WHITE;
			symbol = 'x';
		}
		else if (col == BLACK)
		{
			colour = BLACK;
			symbol = 'o';
		}
		else
		{
			colour = EMPTY;
			symbol = ' ';
		}
	}
};

typedef Position BOARD[3][3];


int heuristicFunction(const BOARD&);

size_t countArcs(const BOARD& board_state, Colour col_first, Colour col_second);
size_t countLines(const BOARD& board_state, Colour col_first, Colour col_second);
size_t countDiagonals(const BOARD& board_state, Colour col_first, Colour col_second);
size_t countEdges(const BOARD& board_state, Colour col_first, Colour col_second);

bool invalidCoordinates(size_t, size_t);

#endif