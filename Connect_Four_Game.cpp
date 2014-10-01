#include "Connect_Four_Game.hpp"

/*****************************/
/* Board Class Methods       */
/*****************************/

Board::Board()
{
    clearBoard();
    lastCol = -1;
    lastRow = -1;
}

Board::~Board()
{
    
}

bool Board::boardEmpty()
{
    for (register int i = 0; i < COLS; ++i)
    {
        for (register int j = 0; j < ROWS; ++j)
        {
            if (getPiece(i, j) != NoPlayer)
                return false;
        }
    }
    
    return true;
}

bool Board::boardFull()
{
    for (register int i = 0; i < COLS; ++i)
    {
        for (register int j = 0; j < ROWS; ++j)
        {
            if (getPiece(i, j) == NoPlayer)
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
            placePiece(i, j, NoPlayer, true);
    }
}

bool Board::columnFull(int col)
{
    if ( (col < 0) || (col >= COLS) )
    {
        throw std::runtime_error("Invalid \"Board::columnFull\" function argument");
        return false;
    }
    
    for (register int i = 0; i < ROWS; ++i)
    {
        if (getPiece(col, i) == NoPlayer)
            return false;
    }
    
    return true;
}

int Board::getPiece(int col, int row)
{
    if ( (col < 0) || (col >= COLS) || (row < 0) ||(row >= ROWS) )
    {
        throw std::runtime_error("Error: invalid \"Board::getPiece\" function argument");
        return NoPlayer;
    }
    
    if ( (state[col][row] != NoPlayer) && (state[col][row] != Player1) && 
         (state[col][row] != Player2) )
    {
        throw std::runtime_error("Error: unexpected state value");
        return NoPlayer;
    }
    
    return state[col][row];
}

bool Board::placePiece(int col, int row, int player, bool replace = false)
{
    if ( (col < 0) || (col >= COLS) || (row < 0) || (row >= ROWS) ||
         (player < NoPlayer) || (player > Player2) )
    {
        throw std::runtime_error("Error: invalid \"Board::placePiece\" function argument");
        return false;
    }
    
    if ( (replace == false) && (state[col][row] != NoPlayer) )
        return false;
    
    state[col][row] = player;
    
    lastCol = col;
    lastRow = row;
    
    return true;
}


/***************************************/
/* ConnectFourGame Class Methods       */
/***************************************/

ConnectFourGame::ConnectFourGame()
{
    
}