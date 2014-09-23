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

#include "Connect_Four_Main"
#include <vector>

class WindowObject
{
private:
    
    
    
public:
    
    
    
};

class ConnectFourWindow
{
private:
    
    ConnectFourGame& game;
    sf::RenderWindow window;
    sf::Event event;
    sf::View view;
    
public:
    
    ConnectFourWindow();
    ~ConnectFourWindow();
    
    bool update();
    bool addObject;
};

#endif	/* CONNECT_FOUR_GRAPHICS_HPP */

