#include "Connect_Four_Game.hpp"
#include <iostream>
#include <stdexcept>


Move::Move()
{}

Move::Move(int p, int c, int r) : player(p), column(c), row(r)
{}

/*****************************/
/* Board Class Methods       */
/*****************************/

Board::Board()
{
    clearBoard();
    lastMove.column = -1;
    lastMove.row = -1;
    lastMove.player = NO_PLR;
}

bool Board::isEmpty()
{
    for (register int i = 0; i < COLS; ++i)
    {
        for (register int j = 0; j < ROWS; ++j)
        {
            if (getPiece(i, j) != NO_PLR)
                return false;
        }
    }
    
    return true;
}

bool Board::isFull()
{
    for (register int i = 0; i < COLS; ++i)
    {
        for (register int j = 0; j < ROWS; ++j)
        {
            if (getPiece(i, j) == NO_PLR)
                return false;
        }
    }
    
    return true;
}

void Board::clearBoard()
{
    for (register int i = 0; i < COLS; ++i)
    {
        for (register int j = 0; j < ROWS; ++j)
            placePiece(i, j, NO_PLR, true);
    }
}

bool Board::columnFull(int col)
{
    if ( (col < 0) || (col >= COLS) )
    {
        throw std::runtime_error("Error: invalid \"Board::columnFull\" function argument");
        return false;
    }
    
    for (register int i = 0; i < ROWS; ++i)
    {
        if (getPiece(col, i) == NO_PLR)
            return false;
    }
    
    return true;
}

int Board::getPiece(int col, int row)
{
    if ( (col < 0) || (col >= COLS) || (row < 0) ||(row >= ROWS) )
    {
        return NO_PLR;
    }
    
    if ( (state[col][row] != NO_PLR) && (state[col][row] != PLR_1) && 
         (state[col][row] != PLR_2) )
    {
        throw std::runtime_error("Error: unexpected state value");
        return NO_PLR;
    }
    
    return state[col][row];
}

bool Board::placePiece(int col, int row, int player, bool replace)
{
    if ( (col < 0) || (col >= COLS) || (row < 0) || (row >= ROWS) ||
         (player < NO_PLR) || (player > PLR_2) )
    {
        throw std::runtime_error("Error: invalid \"Board::placePiece\" function argument");
        return false;
    }
    
    if ( (replace == false) && (state[col][row] != NO_PLR) )
        return false;
    
    state[col][row] = player;
    
    lastMove.column = col;
    lastMove.row = row;
    lastMove.player = player;
    
    return true;
}


/***************************************/
/* ConnectFourGame Class Methods       */
/***************************************/

ConnectFourGame::ConnectFourGame()
{
    p1Score = 0;
    p2Score = 0;
    round = 0;
    roundWinner = NO_PLR;
    activePlayer = PLR_1;
    p1Type = HUMAN;
    p2Type = HUMAN;
    roundWon = false;
    
    moves.reserve(42);

    setNewRound();
}

bool ConnectFourGame::addPoints(int player, int points)
{
    if ( (player < PLR_1) || (player > PLR_2) )
    {
        std::runtime_error("Error: invalid \"ConnectFourGame::addPoints\" function argument");
        return false;
    }

    if (player == PLR_1)
    {
        p1Score += points;
    }

    if (player == PLR_2)
    {
        p2Score += points;
    }

    return true;
}

/*int ConnectFourGame::checkWin(Move move)
{
    int score = 0;
    register int i;
    
    for (i = 0; i < 4; ++i)
    {
        if ( (board.getPiece(move.cloumn, move.row) == move.player) &&
              )
    }
}*/

int ConnectFourGame::checkWin(Move lastMove)
{
    int score = 0;
    int col = lastMove.column;
    int row = lastMove.row;
    int player = lastMove.player;

    if( (board.getPiece(col, row-1) == player) &&  // x
        (board.getPiece(col, row-2) == player) &&  // o
        (board.getPiece(col, row-3) == player) ){  // o

        ++score;
    }///////////////////////////////////////////////////////////////////////////
    if( (board.getPiece(col-1, row-1) == player) &&  //    x
        (board.getPiece(col-2, row-2) == player) &&  //   o
        (board.getPiece(col-3, row-3) == player) ){  //  o
                                                     // o
        ++score;
    }
    if( (board.getPiece(col+1, row+1) == player) &&  //    o
        (board.getPiece(col-1, row-1) == player) &&  //   x
        (board.getPiece(col-2, row-2) == player) ){  //  o
                                                     // o
        ++score;
    }
    if( (board.getPiece(col+1, row+1) == player) &&  //    o
        (board.getPiece(col+2, row+2) == player) &&  //   o
        (board.getPiece(col-1, row-1) == player) ){  //  x
                                                     // o
        ++score;
    }
    if( (board.getPiece(col+1, row+1) == player) &&  //    o
        (board.getPiece(col+2, row+2) == player) &&  //   o
        (board.getPiece(col+3, row+3) == player) ){  //  o
                                                     // x
        ++score;
    } //////////////////////////////////////////////////////////////////////////
    if( (board.getPiece(col+1, row-1) == player) &&  // x
        (board.getPiece(col+2, row-2) == player) &&  //  o
        (board.getPiece(col+3, row-3) == player) ){  //   o
                                                     //    o
        ++score;
    }
    if( (board.getPiece(col-1, row+1) == player) &&  // o
        (board.getPiece(col+1, row-1) == player) &&  //  x
        (board.getPiece(col+2, row-2) == player) ){  //   o
                                                     //    o
        ++score;
    }
    if( (board.getPiece(col-1, row+1) == player) &&  // o
        (board.getPiece(col-2, row+2) == player) &&  //  o
        (board.getPiece(col+1, row-1) == player) ){  //   x
                                                     //    o
        ++score;
    }
    if( (board.getPiece(col-1, row+1) == player) &&  // o
        (board.getPiece(col-2, row+2) == player) &&  //  o
        (board.getPiece(col-3, row+3) == player) ){  //   o
                                                     //    x
        ++score;
    } //////////////////////////////////////////////////////////////////////////
    if( (board.getPiece(col+1, row) == player) &&  // x o o o
        (board.getPiece(col+2, row) == player) &&  //
        (board.getPiece(col+3, row) == player) ){  //
                                                   //
        ++score;
    }
    if( (board.getPiece(col-1, row) == player) &&  // o x o o
        (board.getPiece(col+1, row) == player) &&  //
        (board.getPiece(col+2, row) == player) ){  //
                                                   //
        ++score;
    }
    if( (board.getPiece(col-1, row) == player) &&  // o o x o
        (board.getPiece(col-2, row) == player) &&  //
        (board.getPiece(col+1, row) == player) ){  //
                                                   //
        ++score;
    }
    if( (board.getPiece(col-1, row) == player) &&  // o o o x
        (board.getPiece(col-2, row) == player) &&  //
        (board.getPiece(col-3, row) == player) ){  //
                                                   //
        ++score;
    }
    
    if (score > 0)
    {
        return score;
    }

    if ( board.isFull() )
    {
        return TIE;
    }

    return NO_PLR;
}

int ConnectFourGame::dropPiece(int col, int player)
{   
    int result;
    Move move;
    
    if ( board.columnFull(col) )
    {
        return -1;
    }

    for (register int r = 0; r < ROWS; ++r)
    {
        if ( board.placePiece(col, r, player, false) )
        {
            move.player = player;
            move.column = col;
            move.row = r;
            
            moves.push_back(move);
            
            return r;
        }
    }
    
    return -1;
}

int ConnectFourGame::getScore(int player)
{
    if (player == PLR_1)
    {
        return p1Score;
    }
    else if (player == PLR_2)
    {
        return p2Score;
    }
    
    return -1;
}

int ConnectFourGame::getPlayerType(int player)
{
    if ((player != PLR_1) && (player != PLR_2))
    {
        throw std::runtime_error("Error: invalid \"ConnectFourGame::getPlayerType\" function argument");
        return -1;
    }
    
    if (player == PLR_1)
        return p1Type;
    
    if (player == PLR_2)
        return p2Type;
}

Move ConnectFourGame::getLastMove(void)
{
    return moves.back();
}

bool ConnectFourGame::setNewRound(void)
{
    board.clearBoard();
    ++round;
    roundWinner = NO_PLR;
    roundWon = false;
    activePlayer = ( (round % 2) == 1) ? PLR_1: PLR_2;
    newRound = true;
    
    moves.clear();
    
    return true;
}

void ConnectFourGame::setPlayerType(int player, int type)
{
    if (player == PLR_1)
    {
        p1Type = type;
    }
    
    if (player == PLR_2)
    {
        p2Type = type;
    }
}

bool ConnectFourGame::setRoundWinner(int winner)
{
    if ( (winner != TIE) && (winner != NO_PLR) && 
         (winner != PLR_1) && (winner != PLR_2) )
    {
        return false;
    }
    
    roundWinner = winner;
    roundWon = true;
    
    return true;
}