/* 
 * File:   Connect_Four_Game.hpp
 * Author: Sean
 *
 * Created on September 21, 2014, 3:57 PM
 */

#ifndef CONNECT_FOUR_GAME_HPP
#define	CONNECT_FOUR_GAME_HPP

#include "Connect_Four_Main.hpp"

const int COLS = 7;
const int ROWS = 6;
const int TOP_ROW = 5;

enum Players
{
    Tie = -1,
    NoPlayer,
    Player1,
    Player2,
};

class Board
{
private:
    int     state[COLS][ROWS];
    bool    fullCol[COLS];
    bool    boardEmpty, boardFull;
    int     lastCol, lastRow;

public:
    Board();
    
    bool    boardFull(void);
    bool    clearBoard(void);
    bool    columnFull(int col);
    int     getPiece(int col, int row);
    bool    placePiece(int col, int row, int player, bool replace = false);

    bool    boardFull(void){ return boardFull; }
    int     getLastCol(void){ return lastCol; }
    int     getLastRow(void){ return lastRow; }
    bool    isEmpty(void){ return boardEmpty; }
};

class ConnectFourGame
{
private:
    int                 p1Score, p2Score, round; 
    int                 roundWinner, activePlayer;
    bool                roundWon, newRound;
    ConnectFourWindow&  cfWindow;

public:
    Board   board;

    ConnectFourGame();
    bool    addPoints(int player, int points);
    int     checkWin(int player);
    bool    dropPiece(int col, int player);
    bool    dropPieceAuto(int col, int player);
    int     getScore(int player);
    bool    setNewRound(void);
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

