#include "Heuristic_function.h"

int heuristicFunction(const BOARD& board_state)
{
    int TwoWhiteOneEmpty = countArcs(board_state, EMPTY, WHITE);
    int ThreeWhite       = countArcs(board_state, WHITE, WHITE);
    int OneWhiteTwoEmpty = countArcs(board_state, WHITE, EMPTY);
    int TwoBlackOneEmpty = countArcs(board_state, EMPTY, BLACK);
    int ThreeBlack       = countArcs(board_state, BLACK, BLACK);
    int OneBlackTwoEmpty = countArcs(board_state, BLACK, EMPTY);
    int result = ((2*(TwoWhiteOneEmpty + 2*ThreeWhite) + OneWhiteTwoEmpty) -
                  (2 * (TwoBlackOneEmpty + 2*ThreeBlack) + OneBlackTwoEmpty));
    return result;
}


size_t countArcs(const BOARD& board_state, Colour col_first, Colour col_second)
{
    
    size_t counter = countLines(board_state, col_first, col_second) + countEdges(board_state, col_first, col_second) + countDiagonals(board_state, col_first, col_second);

    return counter;
}

size_t countLines(const BOARD& board_state, Colour col_first, Colour col_second)
{
    size_t counter = 0;

    for (size_t row_cnt = 0; row_cnt < MAX_SIZE; ++row_cnt) // check by row
    {
        if (
            (board_state[row_cnt][0].colour == col_first  && board_state[row_cnt][1].colour == col_second && board_state[row_cnt][2].colour == col_second) ||
            (board_state[row_cnt][0].colour == col_second && board_state[row_cnt][1].colour == col_first  && board_state[row_cnt][2].colour == col_second) ||
            (board_state[row_cnt][0].colour == col_second && board_state[row_cnt][1].colour == col_second && board_state[row_cnt][2].colour == col_first))
        {
            ++counter;
        }
    }
    for (size_t col_cnt = 0; col_cnt < MAX_SIZE; ++col_cnt) // check by column
    {
        if (
            (board_state[0][col_cnt].colour == col_first  && board_state[1][col_cnt].colour == col_second && board_state[2][col_cnt].colour == col_second) ||
            (board_state[0][col_cnt].colour == col_second && board_state[1][col_cnt].colour == col_first  && board_state[2][col_cnt].colour == col_second) ||
            (board_state[0][col_cnt].colour == col_second && board_state[1][col_cnt].colour == col_second && board_state[2][col_cnt].colour == col_first))
        {
            ++counter;
        }
    }
    return counter;
}

size_t countEdges(const BOARD& board_state, Colour col_first, Colour col_second)
{
    size_t counter = 0;

    //checks upper left corner
    if (
        (board_state[1][0].colour == col_first  && board_state[0][0].colour == col_second && board_state[0][1].colour == col_second) ||
        (board_state[1][0].colour == col_second && board_state[0][0].colour == col_first  && board_state[0][1].colour == col_second) ||
        (board_state[1][0].colour == col_second && board_state[0][0].colour == col_second && board_state[0][1].colour == col_first))
    {
        ++counter;
    }
    //checks upper right corner
    if (
        (board_state[0][1].colour == col_first  && board_state[0][2].colour == col_second && board_state[1][2].colour == col_second) ||
        (board_state[0][1].colour == col_second && board_state[0][2].colour == col_first  && board_state[1][2].colour == col_second) ||
        (board_state[0][1].colour == col_second && board_state[0][2].colour == col_second && board_state[1][2].colour == col_first))
    {
        ++counter;
    }
    //checks down left
    if (
        (board_state[1][0].colour == col_first  && board_state[2][0].colour == col_second && board_state[2][1].colour == col_second) ||
        (board_state[1][0].colour == col_second && board_state[2][0].colour == col_first  && board_state[2][1].colour == col_second) ||
        (board_state[1][0].colour == col_second && board_state[2][0].colour == col_second && board_state[2][1].colour == col_first))
    {
        ++counter;
    }
    //checks down right
    if (
        (board_state[2][1].colour == col_first  && board_state[2][2].colour == col_second && board_state[1][2].colour == col_second) ||
        (board_state[2][1].colour == col_second && board_state[2][2].colour == col_first  && board_state[1][2].colour == col_second) ||
        (board_state[2][1].colour == col_second && board_state[2][2].colour == col_second && board_state[1][2].colour == col_first))
    {
        ++counter;
    }
    return counter;
}

size_t countDiagonals(const BOARD& board_state, Colour col_first, Colour col_second)
{
    size_t counter = 0;

    //checks main diagonal
    if (
        (board_state[0][0].colour == col_first  && board_state[1][1].colour == col_second && board_state[2][2].colour == col_second) ||
        (board_state[0][0].colour == col_second && board_state[1][1].colour == col_first  && board_state[2][2].colour == col_second) ||
        (board_state[0][0].colour == col_second && board_state[1][1].colour == col_second && board_state[2][2].colour == col_first))
    {
        ++counter;
    }
    //checks reverse diagonal
    if (
        (board_state[2][0].colour == col_first  && board_state[1][1].colour == col_second && board_state[0][2].colour == col_second) ||
        (board_state[2][0].colour == col_second && board_state[1][1].colour == col_first  && board_state[0][2].colour == col_second) ||
        (board_state[2][0].colour == col_second && board_state[1][1].colour == col_second && board_state[0][2].colour == col_first))
    {
        ++counter;
    }
    return counter;
}

bool invalidCoordinates(size_t x_coord, size_t y_coord)
{
    bool flag = (0 >= x_coord || x_coord >= 2 || 0 >= y_coord || y_coord >= 2);
    return  !flag;
//    return (0 >= x_coord || x_coord >= 2 || 0 >= y_coord || y_coord >= 2);
}