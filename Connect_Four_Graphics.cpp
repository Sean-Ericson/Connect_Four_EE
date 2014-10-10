
#include "Connect_Four_Graphics.hpp"

ConnectFourWindow::ConnectFourWindow()
{
    window.create(sf::VideoMode(InitWinX, InitWinY, 32), "Connect Four");
    
    /*if ( icon.loadFromFile( "weed.bmp" ) )
    {
        std::cout << "Wassup?" << std::endl;
        window.setIcon(48, 48, icon.getPixelsPtr() );
    }*/
    
    colSelectPos = 3;
    
    if (!font.loadFromFile("Font/COMMUNIS.ttf"))
        throw std::runtime_error("Error: failure to load font");
    
    
    view.setCenter( sf::Vector2f( InitWinX / 2, InitWinY / 2 ) );
    view.setSize( sf::Vector2f(InitWinX, InitWinY) );
    
    window.setKeyRepeatEnabled(false);
    window.setView(view);
    
    p1Color = sf::Color::Red;
    p2Color = sf::Color::Black;
}

void ConnectFourWindow::handleKeyPress()
{
    
}

void ConnectFourWindow::handleResize()
{
    bool limitWindowSize = true;
    int minWindowSize = 71, smallSide;
    
    if ( (limitWindowSize) && (event.size.height < minWindowSize) )
    {
        event.size.height = minWindowSize;
        window.setSize( sf::Vector2u(event.size.width, event.size.height) );
    }
    
    view.setSize(event.size.width, event.size.height);
    
    if (event.size.width <= event.size.height)
    {
        view.zoom(1.0 * InitWinX / event.size.width);
    }
    else
    {
        view.zoom(1.0 * InitWinY / event.size.height);
    }

    window.setView(view);
}

void ConnectFourWindow::runGame()
{
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::Resized)
            {
                handleResize();
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                handleKeyPress();
            }
            
            while (window.pollEvent(event)){}
        }
        
        update();
    }
}

bool ConnectFourWindow::update()
{
    
}