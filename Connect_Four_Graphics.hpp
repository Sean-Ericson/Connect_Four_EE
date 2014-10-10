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

const int InitWinX = 712;
const int InitWinY = 440;

const int BoardPosX = 10;
const int BoardPosY = 70;
const int BoardWidth = 420;
const int BoardHeight = 360;

const sf::Color BackGroundColor = sf::Color(185,122,87);

class ConnectFourWindow
{
private:
    
    ConnectFourGame& game;
    sf::RenderWindow window;
    sf::Event event;
    sf::View view;
    sf::Font font;
    
    sf::Color p1Color, p2Color;
    
    int colSelectPos;
    
public:
    
    ConnectFourWindow();
    ~ConnectFourWindow();
    
    void    handleKeyPress(void);
    void    handleResize(void);
    void    runGame(void);
    bool    setGame(ConnectFourGame& game);
    bool    setup(void);
    bool    update(void);
};

#endif	/* CONNECT_FOUR_GRAPHICS_HPP */

