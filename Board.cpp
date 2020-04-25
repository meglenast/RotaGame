#include "Board.h"

Board::Board()
{
    initMoveGraph();
}

//public:
void Board::initBoard(size_t first)
{
    printBoard();
    if (first) //first == true  -> AI do first move
    {
        for (size_t i = 0; i < 3; ++i)
        {
            initAI();
            printBoard();
            initPlayer();
            printBoard();
            clearConsole();
        }
    }
    else // player do first move
    {
        for (size_t i = 0; i < 3; ++i)
        {
            initPlayer();
            clearConsole();
            printBoard();
            initAI();
            printBoard();
            clearConsole();
        }
    }
}


void Board::printBoard()const
{
    printTitel();
    std::cout << "   0    0    1    2    2  " << std::endl;
    std::cout << "__________________________" << std::endl << std::endl;
    for (size_t curr_row = 0; curr_row < 5; ++curr_row)
    {
        printRow(curr_row);
    }
}

void Board::printRow(size_t row_index)const
{
    if (row_index == 0 || row_index == 4)
    {
        std::cout << " ";
        printSemiRow(2, BLACK_SQUARE);
        printSemiRow(1, WHITE_SQUARE);
        printSemiRow(2, BLACK_SQUARE);
        
        if (row_index == 0)
            std::cout << std::endl<< "0";
        else
            std::cout << std::endl<<"2";
        
        printSemiRow(2, BLACK_SQUARE);
        if (row_index == 0)
            std::cout << WHITE_SQUARE << WHITE_SQUARE << rota_board[0][1].symbol << WHITE_SQUARE << WHITE_SQUARE;
        else if (row_index == 4)
            std::cout << WHITE_SQUARE << WHITE_SQUARE << rota_board[2][1].symbol << WHITE_SQUARE << WHITE_SQUARE;
        printSemiRow(2, BLACK_SQUARE);
        std::cout << std::endl << " ";;
        printSemiRow(2, BLACK_SQUARE);
        printSemiRow(1, WHITE_SQUARE);
        printSemiRow(2, BLACK_SQUARE);
        std::cout << std::endl;
    }
    else if  (row_index == 2)
    {
        std::cout << " ";
        printSemiRow(5, WHITE_SQUARE);
        std::cout << std::endl<< "1";
        std::cout << WHITE_SQUARE << WHITE_SQUARE << rota_board[1][0].symbol << WHITE_SQUARE << WHITE_SQUARE;
        printSemiRow(1, WHITE_SQUARE);
        std::cout << WHITE_SQUARE << WHITE_SQUARE << rota_board[1][1].symbol << WHITE_SQUARE << WHITE_SQUARE;
        printSemiRow(1, WHITE_SQUARE);
        std::cout << WHITE_SQUARE << WHITE_SQUARE << rota_board[1][2].symbol << WHITE_SQUARE << WHITE_SQUARE << std::endl << " ";
        printSemiRow(5, WHITE_SQUARE);
        std::cout << std::endl;
    }
    else if (row_index == 1 || row_index == 3)
    {
        std::cout << " ";
        printSemiRow(1, BLACK_SQUARE);
        printSemiRow(3, WHITE_SQUARE);
        printSemiRow(1, BLACK_SQUARE);
        if (row_index == 1)
            std::cout << std::endl << "0";
        else
            std::cout << std::endl <<"2";

        printSemiRow(1, BLACK_SQUARE);
        std::cout << WHITE_SQUARE << WHITE_SQUARE;

        if (row_index == 1)
        {
            std::cout << rota_board[0][0].symbol << WHITE_SQUARE << WHITE_SQUARE;
            printSemiRow(1, WHITE_SQUARE);
            std::cout << WHITE_SQUARE << WHITE_SQUARE << rota_board[0][2].symbol;
        }
        else if (row_index == 3)
        {
            std::cout << rota_board[2][0].symbol << WHITE_SQUARE << WHITE_SQUARE;
            printSemiRow(1, WHITE_SQUARE);
            std::cout << WHITE_SQUARE << WHITE_SQUARE << rota_board[2][2].symbol;
        }

        std::cout << WHITE_SQUARE << WHITE_SQUARE;
        printSemiRow(1, BLACK_SQUARE);
        std::cout << std::endl << " ";
        printSemiRow(1, BLACK_SQUARE);
        printSemiRow(3, WHITE_SQUARE);
        printSemiRow(1, BLACK_SQUARE);
        std::cout << std::endl;
    }
}

void Board::printSemiRow(size_t num_squares, char colour)const
{
    for (size_t i = 0; i < num_squares * 5; ++i)
        std::cout << colour;
}

void Board::getBestMove(std::queue<State>& history)
{
    int best_score = MIN_INF;
    Coordinates bestMoveTo;
    Coordinates bestMoveFrom;

    for (size_t row_cnt = 0; row_cnt < MAX_SIZE; ++row_cnt)
    {
        for (size_t col_cnt = 0; col_cnt < MAX_SIZE; ++col_cnt)
        {
            if (rota_board[row_cnt][col_cnt].colour == WHITE)
            {
                for (size_t i = 0; i < moves[row_cnt][col_cnt].size(); ++i)
                {
                    size_t next_x = moves[row_cnt][col_cnt][i].x_coord;
                    size_t next_y = moves[row_cnt][col_cnt][i].y_coord;
                    if (rota_board[next_x][next_y].colour == EMPTY)
                    {
                        rota_board[row_cnt][col_cnt].setCell(EMPTY);
                        rota_board[next_x][next_y].setCell(WHITE);

                        int alpha_val = MIN_INF;
                        int beta_val = PLUS_INF;
                       
                        State curr;
                        copyCurrBoard(curr);

                        int curr_value = miniMax(curr, 0, false, MIN_INF, PLUS_INF);

                        rota_board[row_cnt][col_cnt].setCell(WHITE);
                        rota_board[next_x][next_y].setCell(EMPTY);

                        if (curr_value > best_score)
                        {
                            bestMoveFrom.x_coord = row_cnt;
                            bestMoveFrom.y_coord = col_cnt;
                            bestMoveTo.x_coord = next_x;
                            bestMoveTo.y_coord = next_y;
                            best_score = curr_value;
                        }
                    }
                }
            }
        }
    }
    rota_board[bestMoveFrom.x_coord][bestMoveFrom.y_coord].setCell(EMPTY);
    rota_board[bestMoveTo.x_coord][bestMoveTo.y_coord].setCell(WHITE);

    addBoardConfiguration(history);
    clearConsole();
    printBoard();
}

int Board::miniMax(State state, size_t depth, bool isMax, int alpha, int beta)
{
    int state_value = heuristicFunction(state.board);

    if (finalState(WHITE))
        return state_value;
    if (finalState(BLACK))
        return state_value;
    if (depth == MAX_DEPTH)
        return state_value;

    if (isMax)
    {
        int best_score = MIN_INF;

        for (size_t curr_row = 0; curr_row < MAX_SIZE; ++curr_row)
        {
            for (size_t curr_col = 0; curr_col < MAX_SIZE; ++curr_col)
            {
                if (state.board[curr_row][curr_col].colour == WHITE)
                {
                    for (size_t i = 0; i < moves[curr_row][curr_col].size(); ++i)
                    {
                        Coordinates next_move(moves[curr_row][curr_col][i].x_coord, moves[curr_row][curr_col][i].y_coord);
                        
                        State curr;
                        copyPrevState(state, curr);
                        curr.board[next_move.x_coord][next_move.y_coord].setCell(WHITE);
                        curr.board[curr_row][curr_col].setCell(EMPTY);
                        
                        best_score = std::max(best_score, miniMax(curr, depth + 1, !isMax, alpha, beta));
                        alpha = std::max(alpha, best_score);

                        if (beta <= alpha)
                            break;
                    }
                }
            }
        }
        return best_score;
    }
    else
    {
        int best_score = PLUS_INF;

        for (size_t curr_row = 0; curr_row < MAX_SIZE; ++curr_row)
        {
            for (size_t curr_col = 0; curr_col < MAX_SIZE; ++curr_col)
            {
                if (state.board[curr_row][curr_col].colour == BLACK)
                {
                    for (size_t i = 0; i < moves[curr_row][curr_col].size(); ++i)
                    {
                        Coordinates next_move(moves[curr_row][curr_col][i].x_coord, moves[curr_row][curr_col][i].y_coord);
                        
                        State curr;
                        copyPrevState(state, curr);

                        curr.board[next_move.x_coord][next_move.y_coord].setCell(BLACK);
                        curr.board[curr_row][curr_col].setCell(EMPTY);
                        
                        best_score = std::min(best_score, miniMax(curr, depth + 1, !isMax, alpha, beta));
                        beta = std::min(beta, best_score);

                        if (beta <= alpha)
                            break;
                    }
                }
            }
        }
        return best_score;
    }
}

void Board::getPlayersMove(std::queue<State>& history)
{
    printBoard();
    int x_from, y_from = -1;
    while (true)
    {
        std::cout << "Enter the coordinates of the piece you want  to move:";
        std::cin >> x_from >> y_from;
        if (invalidCoordinates(x_from, y_from) || rota_board[x_from][y_from].colour != BLACK)
            std::cout << "Invalid coordinates, try again\n";
        else
            break;
    }
    int x_to, y_to = -1;
    while (true)
    {
        std::cout << "\nEnter the coordinates of the position where you want to move your piece:";
        std::cin >> x_to >> y_to;
        if (invalidCoordinates(x_to, y_to) || rota_board[x_to][y_to].colour != EMPTY || !isAdjecentCell(x_from, y_from, x_to, y_to))
            std::cout << "Invalid coordinates, try again\n";
        else
            break;
    }
    rota_board[x_from][y_from].setCell(EMPTY);
    rota_board[x_to][y_to].setCell(BLACK);

    addBoardConfiguration(history);
    clearConsole();
    printBoard();
}

bool Board::isEmpty(int x_coord, int y_coord)const
{
    return rota_board[x_coord][y_coord].colour == EMPTY;
}

void Board::setMove(int x_coord, int y_coord, Colour colour)
{
    rota_board[x_coord][y_coord].setCell(colour);
}

//private:

void Board::initMoveGraph()
{
    for (size_t row_cnt = 0; row_cnt < MAX_SIZE; ++row_cnt)
        for (size_t col_cnt = 0; col_cnt < MAX_SIZE; ++col_cnt)
            pushPossibleMoves(row_cnt, col_cnt);
}

void Board::pushPossibleMoves(size_t row, size_t col)
{
    Coordinates curr(row, col);
    if (Coordinates(0, 0) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); //right, down, centere
        moves[row][col].push_back(Coordinates(0, 1));
        moves[row][col].push_back(Coordinates(1, 0));
    }
    else if (Coordinates(0, 1) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); // left, right, centere
        moves[row][col].push_back(Coordinates(0, 0));
        moves[row][col].push_back(Coordinates(0, 2));
    }
    else if (Coordinates(0, 2) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); // left, down, centere
        moves[row][col].push_back(Coordinates(0, 1));
        moves[row][col].push_back(Coordinates(1, 2));
    }
    else if (Coordinates(1, 0) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); // up, down, centere
        moves[row][col].push_back(Coordinates(0, 0));
        moves[row][col].push_back(Coordinates(2, 0));
    }
    else if (Coordinates(1, 1) == curr)
    {
        moves[row][col].push_back(Coordinates(0, 0)); // all directions
        moves[row][col].push_back(Coordinates(0, 1));
        moves[row][col].push_back(Coordinates(0, 2));
        moves[row][col].push_back(Coordinates(1, 0));
        moves[row][col].push_back(Coordinates(1, 2));
        moves[row][col].push_back(Coordinates(2, 0));
        moves[row][col].push_back(Coordinates(2, 1));
        moves[row][col].push_back(Coordinates(2, 2));
    }
    else if (Coordinates(1, 2) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); // up, down, centere
        moves[row][col].push_back(Coordinates(0, 2));
        moves[row][col].push_back(Coordinates(2, 2));
    }
    else if (Coordinates(2, 0) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); // up, right, centere
        moves[row][col].push_back(Coordinates(1, 0));
        moves[row][col].push_back(Coordinates(2, 1));
    }
    else if (Coordinates(2, 1) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); // left, right, centere
        moves[row][col].push_back(Coordinates(2, 0));
        moves[row][col].push_back(Coordinates(2, 2));
    }
    else if (Coordinates(2, 2) == curr)
    {
        moves[row][col].push_back(Coordinates(1, 1)); // left, up, centere
        moves[row][col].push_back(Coordinates(2, 1));
        moves[row][col].push_back(Coordinates(1, 2));
    }
}


void Board::initAI()
{
    int best_x;
    int best_y;
    int best_value = MIN_INF;

    if (boardEmpty())
    {
        best_x = rand() % 3;
        best_y = rand() % 3;
    }
    else
    {
        for (size_t row = 0; row < MAX_SIZE; ++row)
        {
            for (size_t col = 0; col < MAX_SIZE; ++col)
            {
                if (rota_board[row][col].colour == EMPTY)
                {
                    rota_board[row][col].setCell(WHITE);

                    int val = heuristicFunction(rota_board);

                    if (val > best_value)
                    {
                        best_value = val;
                        best_x = row;
                        best_y = col;
                    }
                    rota_board[row][col].setCell(EMPTY);
                }
            }
        }
    
    }
    
    rota_board[best_x][best_y].setCell(WHITE);
}

void Board::initPlayer()
{
    int x_coord, y_coord;
    while (true)
    {
        std::cout << "Enter the coordinates of the  Position: ";
        std::cin >> x_coord >> y_coord;
        std::cout << std::endl;
        if (rota_board[x_coord][y_coord].colour != EMPTY || invalidCoordinates(x_coord, y_coord))
        {
            std::cout << "Invaid coordinates." << std::endl;
        }
        else
        {
            rota_board[x_coord][y_coord].setCell(BLACK);
            return;
        }
    }
}

bool Board::finalState(Colour player_col)const
{
    return threeInLine(player_col) || threeInDiagonal(player_col) || threeOnEdge(player_col);
}

bool Board::threeInLine(Colour player_col)const
{
    for (size_t row_cnt = 0; row_cnt < MAX_SIZE; ++row_cnt) //horizontal check
        if (rota_board[row_cnt][0].colour == player_col && rota_board[row_cnt][1].colour == player_col && rota_board[row_cnt][2].colour == player_col)
            return true;
    for (size_t col_cnt = 0; col_cnt < MAX_SIZE; ++col_cnt) //vertical check
        if (rota_board[0][col_cnt].colour == player_col && rota_board[1][col_cnt].colour == player_col && rota_board[2][col_cnt].colour == player_col)
            return true;
    return false;
}

bool Board::threeInDiagonal(Colour player_col)const
{
    if (rota_board[0][0].colour == player_col && rota_board[1][1].colour == player_col && rota_board[2][2].colour == player_col)
        return true;
    if (rota_board[2][0].colour == player_col && rota_board[1][1].colour == player_col && rota_board[0][2].colour == player_col)
        return true;
    return false;
}

bool Board::threeOnEdge(Colour player_col)const
{
    if (rota_board[1][0].colour == player_col && rota_board[0][0].colour == player_col && rota_board[0][1].colour == player_col)
        return true;
    if (rota_board[0][1].colour == player_col && rota_board[0][2].colour == player_col && rota_board[1][2].colour == player_col)
        return true;
    if (rota_board[1][0].colour == player_col && rota_board[2][0].colour == player_col && rota_board[2][1].colour == player_col)
        return true;
    if (rota_board[2][1].colour == player_col && rota_board[2][2].colour == player_col && rota_board[1][2].colour == player_col)
        return true;
    return false;
}

bool Board::isAdjecentCell(size_t x_from, size_t y_from, size_t x_to, size_t y_to)const
{
    for (size_t i = 0; i < moves[x_from][y_from].size(); ++i)
        if (moves[x_from][y_from][i].x_coord == x_to && moves[x_from][y_from][i].y_coord == y_to)
            return true;

    return false;
}

void Board::addBoardConfiguration(std::queue<State>& history)const
{
    State curr;

    for (size_t curr_row = 0; curr_row < MAX_SIZE; ++curr_row)
    {
        for (size_t curr_col = 0; curr_col < MAX_SIZE; ++curr_col)
            curr.board[curr_row][curr_col].setCell(rota_board[curr_row][curr_col].colour);
    }
    history.push(curr);
}
void Board::copyCurrBoard(State& state)const
{
    for (size_t i = 0; i < MAX_SIZE; ++i)
        for (size_t j = 0; j < MAX_SIZE; ++j)
            state.board[i][j].setCell(rota_board[i][j].colour);
}
void Board::copyPrevState(const State& prev, State& curr)
{
    for (size_t row = 0; row < MAX_SIZE; ++row)
        for (size_t col = 0; col < MAX_SIZE; ++col)
            curr.board[row][col].setCell(prev.board[row][col].colour);
}
bool Board::boardEmpty()const
{
    for (size_t row = 0; row < MAX_SIZE; ++row)
    {
        for (size_t col = 0; col < MAX_SIZE; ++col)
            if (rota_board[row][col].colour != EMPTY)
                return false;
    }
    return true;
}