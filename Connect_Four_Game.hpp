/* 
 * File:   Connect_Four_Game.hpp
 * Author: Sean
 *
 * Created on September 21, 2014, 3:57 PM
 */

#ifndef CONNECT_FOUR_GAME_HPP
#define	CONNECT_FOUR_GAME_HPP

#include "Connect_Four_Main.hpp"
#include <vector>

const int COLS = 7;
const int ROWS = 6;
const int TOP_ROW = 5;
const int HUMAN = 0;
const int AI = 1;

enum Players
{
    Tie = -1,
    NoPlayer,
    Player1,
    Player2,
};

struct Move
{
    int player, column, row;
    
    Move(int p, int c, int r) : player(p), column(c), row(r)
    {}
};

class Board
{
private:
    
    int     state[COLS][ROWS];
    Move    lastMove;

public:
    
    Board();
    ~Board();
    
    bool    isFull(void);
    bool    isEmpty(void);
    void    clearBoard(void);
    bool    columnFull(int col);
    int     getPiece(int col, int row);
    bool    placePiece(int col, int row, int player, bool replace = false);

    int     lastCol(void){ return lastMove.column; }
    int     lastRow(void){ return lastMove.row; }
};

class ConnectFourGame
{
private:
    int                 p1Score, p2Score, round, p1Type, p2Type; 
    int                 roundWinner, activePlayer;
    bool                roundWon, newRound;
    std::vector<Move>   moves;

public:
    Board   board;

    ConnectFourGame();
    ~ConnectFourGame();
    
    bool    addPoints(int player, int points);
    int     checkWin(int player);
    bool    dropPiece(int col, int player); //Returns row it lands in
    //bool    dropPieceAuto(int col, int player);
    int     getScore(int player);
    bool    setNewRound(void);
    void    setPlayerType(int player, bool type);
    bool    setRoundWinner(int winner);
    bool    setWindow(ConnectFourWindow& window);

    int     getActivePlayer(void){ return activePlayer; }
    int     getRounds(void){ return round; }
    int     getRoundWinner(void){ return roundWinner; }
    bool    isNewRound(void){ return newRound; }
    bool    roundIsWon(void){ return roundWon; }
    void    switchPlayerTurn(void){ activePlayer = (activePlayer == Player1) ? Player2 : Player1; }
    //void setRoundWon(bool won){ roundWon = won; }
};

#endif	/* CONNECT_FOUR_GAME_HPP */

