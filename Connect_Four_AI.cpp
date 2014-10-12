#include "Connect_Four_AI.hpp"
#include "Connect_Four_Game.hpp"
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>

MoveAndVal::MoveAndVal()
{}
    
MoveAndVal::MoveAndVal(int m, int v) : move(m), val(v)
{}

int AIselectCol(Board board, int player)
{
    //std::cout << "AIselectCol" << std::endl;
    
    std::vector<MoveAndVal> openCols, bestCols;
    int bestVal;
    
    //Determine what columns aren't full
    for (int i = 0; i < COLS; ++i) 
        if ( !board.columnFull(i) )
            openCols.push_back( MoveAndVal (i, 0) );
    
    //If no columns are full, you're gonna have a bad time
    if (openCols.size() == 0)
        throw std::runtime_error("Error: in function \"AIselectCol\": no open columns");
    
    //Get the value for each column that isn't full
    for (int i = 0; i < openCols.size(); ++i) 
        openCols[i].val = moveVal(board, openCols[i].move, player, player, 1, 2);
    
    std::cout << std::endl;
    
    //Determine the best value;
    bestVal = openCols[0].val;
    std::cout << bestVal << std::endl;
    for (int i = 1; i < openCols.size(); ++i)
    {
        std::cout << openCols[i].val << std::endl;
        if (openCols[i].val > bestVal)
            bestVal = openCols[i].val;
    }
    //Determine which moves share that value
    for (int i = 0; i < openCols.size(); ++i)
        if (openCols[i].val == bestVal)
            bestCols.push_back(openCols[i]);
    
    //Randomly select one of the columns wiht the best value
    return bestCols[ randInt(0, bestCols.size() - 1) ].move;
}

int moveVal(Board board, int col, int AIplayer, int curPlayer, int curDepth, int maxDepth)
{   
    //std::cout << "    moveVal" << std::endl;
    
    //First, generate new board state (node)
    AIdropPiece(col, curPlayer, board);
    
    //Find result of last move
    int CWresult = ConnectFourGame::checkWin(board.getlMove(), board);
        
    //Let ties be equivilant to no win; return that there was a tie
    if (CWresult == -1)
        return 0;
    
    //if the current player is not the AI, make the checkWin result negative
    if (curPlayer != AIplayer)
    {
        CWresult *= -1;
    }
        
    //If there was a win, return it
    if (CWresult != 0)
        return CWresult;
    
    //If current depth is the maximum depth, return the checkWin result (which should be 0)
    if (curDepth == maxDepth)
        return CWresult;
    
    //If not a current depth yet, find the best value of the best move from this column
    //You are correct if you think this looks a lot like the AIselectCol function...
    std::vector<MoveAndVal> openCols, bestCols;
    int bestVal;
    
    //Determine what columns aren't full
    for (int i = 0; i < COLS; ++i) 
        if ( !board.columnFull(i) )
            openCols.push_back( MoveAndVal (i, 0) );
    
    //If no columns are full, then the last move was a tie, so return that
    if (openCols.size() == 0)
        return 0;
    
    //Get the value for each column that isn't full
    for (int i = 0; i < openCols.size(); ++i) 
        openCols[i].val = moveVal(board, openCols[i].move, AIplayer, (curPlayer == PLR_1) ? PLR_2: PLR_1, curDepth + 1, maxDepth); // RECURSION! =D
    
    //Determine the best value;
    if (curPlayer == AIplayer)
    {
        bestVal = openCols[0].val;
        for (int i = 1; i < openCols.size(); ++i)
            if (openCols[i].val < bestVal)
                bestVal = openCols[i].val;
    }
    else
    {
        bestVal = openCols[0].val;
        for (int i = 1; i < openCols.size(); ++i)
            if (openCols[i].val > bestVal)
                bestVal = openCols[i].val;
    }
    
    return bestVal;
}

int AIdropPiece(int col, int player, Board& fBoard)
{   
    int result;
    Move move;
    
    //std::cout << "        AIdropPiece" << std::endl;
    
    if ( fBoard.columnFull(col) )
    {
        return -1;
    }

    for (register int r = 0; r < ROWS; ++r)
    {
        if ( fBoard.placePiece(col, r, player, false) )   
            return r;
    }
    
    return -1;
}

int randInt( int min, int max )
{
    if( min > max ){
        
        return (min + 1);
    }
    
    return (int)( ( ( rand() / (RAND_MAX * 1.0) ) * (1 + max - min) ) + min );
}
