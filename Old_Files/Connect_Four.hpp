/*
 * File:   Connect_Four.hpp
 * Author: Sean Ericson
 *
 * Created on March 10, 2014, 6:53 AM
 */

#ifndef CONNECT_FOUR_HPP
#define	CONNECT_FOUR_HPP

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
    int state[COLS][ROWS];
    bool fullCol[COLS];
    bool empty, boardFull;
    int lastCol, lastRow;

public:
    Board();
    bool checkBoardFull(void);
    bool clearBoard(void);
    bool colIsFull(int col);
    int getPiece(int col, int row);
    bool placePiece(int col, int row, int player, bool replace);

    bool boardIsFull(void){ return boardFull; }
    //int (*getBoardState(void))[ROWS]{ return state; }
    int getLastCol(void){ return lastCol; }
    int getLastRow(void){ return lastRow; }
    bool isEmpty(void){ return empty; }
};

class ConnectFourGame
{
private:
    int p1Score, p2Score, round, roundWinner;
    bool p1Turn, roundWon, newRound;

public:
    Board board;

    ConnectFourGame();
    bool addPoints(int player, int points);
    int checkWin(int player);
    bool dropPiece(int col, int player);
    bool dropPieceAuto(int col, int player);
    int getScore(int player);
    bool setNewRound(void);
    bool setRoundWinner(int winner);

    int getActivePlayer(void){ return (p1Turn) ? Player1 : Player2; }
    int getRounds(void){ return round; }
    int getRoundWinner(void){ return roundWinner; }
    bool isNewRound(void){ return newRound; }
    bool isP1Turn(void){ return p1Turn; }
    bool roundIsWon(void){ return roundWon; }
    void switchPlayerTurn(void){ p1Turn = !p1Turn; }
    //void setRoundWon(bool won){ roundWon = won; }
};

#endif	/* CONNECT_FOUR_HPP */
