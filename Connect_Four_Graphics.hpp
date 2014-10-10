/* 
 * File:   Connect_Four_Graphics.hpp
 * Author: Sean
 *
 * Created on September 21, 2014, 3:58 PM
 */

#ifndef CONNECT_FOUR_GRAPHICS_HPP
#define	CONNECT_FOUR_GRAPHICS_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Connect_Four_Main.hpp"
#include <vector>

const int INIT_WIN_X = 712;
const int INIT_WIN_Y = 440;

const int BOARD_POS_X = 10;
const int BOARD_POS_Y = 70;
const int BOARD_WIDTH = 420;
const int BOARD_HEIGHT = 360;

const sf::Color BackGroundColor = sf::Color(185,122,87);
const sf::Color P1_CLR = sf::Color::Red;
const sf::Color P2_CLR = sf::Color::Black;

class ConnectFourWindow
{
private:
    
    ConnectFourGame game;
    sf::RenderWindow window;
    sf::Event event;
    sf::View view;
    sf::Font font;
    
    sf::Color p1Color = P1_CLR, p2Color = P2_CLR;
    
    int colSelectPos;
    
public:
    
    ConnectFourWindow();
    
    void        drawInterface(void);
    void        drawBoard(void);
    bool        drawColSelect(void);
    bool        drawScoreBox(void);
    bool        drawWinText(int player);
    bool        dropAnim(const Move move);
    void        handleKeyPress(void);
    void        handleResize(void);
    std::string intToStr(int num);
    void        runGame(void);
    bool        setGame(ConnectFourGame& game);
    bool        setup(void);
    bool        update(void);
};

#endif	/* CONNECT_FOUR_GRAPHICS_HPP */

