
#include "Connect_Four_Graphics.hpp"
#include "Connect_Four_AI.hpp"
#include <cstdio>
#include <iostream>

ConnectFourWindow::ConnectFourWindow()
{
    window.create(sf::VideoMode(INIT_WIN_X, INIT_WIN_Y, 32), "Connect Four");
    
    /*if ( icon.loadFromFile( "weed.bmp" ) )
    {
        std::cout << "Wassup?" << std::endl;
        window.setIcon(48, 48, icon.getPixelsPtr() );
    }*/
    
    colSelectPos = 3;
    
    if (!font.loadFromFile("Font/COMMUNIS.ttf"))
        throw std::runtime_error("Error: failure to load font");
    
    
    view.setCenter( sf::Vector2f( INIT_WIN_X / 2, INIT_WIN_Y / 2 ) );
    view.setSize( sf::Vector2f(INIT_WIN_X, INIT_WIN_Y) );
    
    window.setKeyRepeatEnabled(false);
    window.setView(view);
    
}

void ConnectFourWindow::drawInterface()
{
    window.clear(sf::Color::Cyan);
    
    sf::RectangleShape backGround( sf::Vector2f(INIT_WIN_X, INIT_WIN_Y) );
    backGround.setFillColor(BackGroundColor);
    window.draw(backGround);
    
    drawBoard();
    drawScoreBox();
    
    if (!game.roundIsWon())
    {
        drawColSelect();
    }
    else
    {
        drawWinText( game.getRoundWinner() );
    }
    
    window.display();
}

void ConnectFourWindow::drawBoard(void)
{
    sf::RectangleShape gameBoard( sf::Vector2f(BOARD_WIDTH, BOARD_HEIGHT) );
    gameBoard.setPosition(BOARD_POS_X, BOARD_POS_Y);
    gameBoard.setFillColor(sf::Color::Blue);
    window.draw(gameBoard);
    
    sf::CircleShape circle(20.0, 100);
    
    for (int a = 0; a < 7; ++a)
    {
        for (int b = 0; b < 6; ++b)
        {
            if (game.board.getPiece(a, b) == NO_PLR)
            {
                circle.setFillColor(BackGroundColor);
            }
            else if (game.board.getPiece(a, b) == PLR_1)
            {
                circle.setFillColor(P1_CLR);
            }
            else if (game.board.getPiece(a, b) == PLR_2)
            {
                circle.setFillColor(P2_CLR);
            }
            
            circle.setPosition( BOARD_POS_X + 10 + (60 * a), 
                                BOARD_POS_Y + 310 - (60 * b) );
            window.draw(circle);
        }
    }
}

bool ConnectFourWindow::drawColSelect()
{
    sf::CircleShape piece(20.0, 100);
    
    if (game.getActivePlayer() == PLR_1)
    {
        piece.setFillColor(p1Color);
    }
    else
    {
        piece.setFillColor(p2Color);
    }
    
    piece.setPosition(BOARD_POS_X + 10 + (60 * colSelectPos), 20);
    window.draw(piece);
}

bool ConnectFourWindow::drawScoreBox(void)
{
    sf::RectangleShape box( sf::Vector2f(252, 420) );
    
    sf::Text text;
    
    box.setPosition(450, 10);
    box.setFillColor(BackGroundColor);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(-2.0);
    window.draw(box);
    
    box.setSize( sf::Vector2f(252, 60) );
    window.draw(box);
    
    text.setString( "Round " + intToStr( game.getRounds() ) );
    text.setFont(font);
    text.setStyle(sf::Text::Regular);
    text.setCharacterSize(32);
    text.setColor(sf::Color::Black);
    text.setPosition(460, 20); 
    window.draw(text);
    
    text.setString("Player 1's Score:");
    text.setColor(p1Color);
    text.setCharacterSize(24);
    text.setPosition(460, 77);
    window.draw(text);
    
    text.setString( intToStr( game.getScore(PLR_1) ) );
    text.setCharacterSize(20);
    text.setPosition(460, 112);
    window.draw(text);
    
    text.setString("Player 2's Score:");
    text.setColor(p2Color);
    text.setCharacterSize(24);
    text.setPosition(460, 155);
    window.draw(text);
    
    text.setString( intToStr( game.getScore(PLR_2) ) );
    text.setCharacterSize(20);
    text.setPosition(460, 190);
    window.draw(text);
}

bool ConnectFourWindow::drawWinText(int player)
{
    sf::Text text;
    
    text.setFont(font);
    text.setStyle(sf::Text::Regular);
    text.setCharacterSize(32);
    text.setPosition(110, 10);
    
    switch (player)
    {
    case PLR_1:
        text.setColor(p1Color);
        text.setString("Player 1 Wins!");
        break;
    
    case PLR_2:
        text.setColor(p2Color);
        text.setString("Player 2 Wins!");
        break;
        
    case TIE:
        text.setColor(sf::Color::Black);
        text.setPosition(145, 10);
        text.setString("TIE Game!");
        break;
    }
    
    window.draw(text);
    
    text.setString("Press Space to Continue");
    text.setColor(sf::Color::Black);
    text.setCharacterSize(15);
    text.setPosition(136, 45);
    
    window.draw(text);
    
    return true;
}

bool ConnectFourWindow::dropAnim(const Move move) //Broken. I have now idea why.
{   
    sf::Clock timingClock;
    sf::Time deltaTime = sf::milliseconds(1000);
    sf::CircleShape piece(20.0, 100), blank(20.0, 100);
    
    if ( (move.player != PLR_1) && (move.player != PLR_2) )
    {
        return false;
    }
    
    piece.setFillColor( (move.player == PLR_1) ? p1Color : p2Color );
    blank.setFillColor(BackGroundColor);
    
    for (register char a = TOP_ROW; a >= move.row; --a)
    {
        timingClock.restart();
        
        blank.setPosition( BOARD_POS_X + 10 + (60 * move.column), 
                           BOARD_POS_Y + 310 - (60 * (a + 1) ) );
        window.draw(blank);
        window.display();
        
        /*piece.setPosition( BOARD_POS_X + 10 + (60 * move.column), 
                           BOARD_POS_Y + 310 - (60 * a) );
        window.draw(piece);
        window.display();*/
        
        while (timingClock.getElapsedTime() < deltaTime){}
    }
    
}

void ConnectFourWindow::handleKeyPress()
{   
    if ( (event.key.code == sf::Keyboard::Left) && !game.roundIsWon() && 
         (game.getPlayerType(game.getActivePlayer()) == HUMAN) && (colSelectPos > 0) )
    {
        --colSelectPos;
    }
    
    if ( (event.key.code == sf::Keyboard::Right) && !game.roundIsWon() && 
         (game.getPlayerType(game.getActivePlayer()) == HUMAN) && (colSelectPos < 6) )
    {
        ++colSelectPos;
    }
    
    if ( (event.key.code == sf::Keyboard::Down) && !game.roundIsWon() &&
         (game.getPlayerType(game.getActivePlayer()) == HUMAN) )
    {
        if ( game.dropPiece(colSelectPos, game.getActivePlayer() ) != -1 )
        {
            //dropAnim( game.getLastMove() );
            colSelectPos = 3;
            int result = game.checkWin(game.getLastMove());
            if (result > 0)
            {
                game.addPoints(game.getActivePlayer(), result);
                drawWinText(game.getActivePlayer());
                game.setRoundWinner(game.getActivePlayer());
            }
            else if (result == TIE)
            {
                drawWinText(TIE);
                game.setRoundWinner(TIE);
            }
            else
            {
                game.switchPlayerTurn();
            }
        }
    }
    
    if ( (event.key.code == sf::Keyboard::Space) && game.roundIsWon() )
    {
        //clearBoardAnim();
        game.setNewRound();
    }
    
    if (event.key.code == sf::Keyboard::Num1)
    {
        if (game.getPlayerType(PLR_1) == HUMAN)
            game.setPlayerType(PLR_1, AI);
        else
            game.setPlayerType(PLR_1, HUMAN);
    }
    
    if (event.key.code == sf::Keyboard::Num2)
    {
        if (game.getPlayerType(PLR_2) == HUMAN)
            game.setPlayerType(PLR_2, AI);
        else
            game.setPlayerType(PLR_2, HUMAN);
    }
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
        view.zoom(1.0 * INIT_WIN_X / event.size.width);
    }
    else
    {
        view.zoom(1.0 * INIT_WIN_Y / event.size.height);
    }

    window.setView(view);
}

std::string ConnectFourWindow::intToStr(int num)
{
    char buff[4];
    sprintf( buff, "%d", num);
    return buff;
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
        
        if ( (!game.roundIsWon()) && (game.getPlayerType(game.getActivePlayer()) == AI) )
        {
            if ( game.dropPiece(AIselectCol(game.board), game.getActivePlayer() ) != -1 )
            {
                //dropAnim( game.getLastMove() );
                colSelectPos = 3;
                int result = game.checkWin(game.getLastMove());
                if (result > 0)
                {
                    game.addPoints(game.getActivePlayer(), result);
                    drawWinText(game.getActivePlayer());
                    game.setRoundWinner(game.getActivePlayer());
                }
                else if (result == TIE)
                {
                    drawWinText(TIE);
                    game.setRoundWinner(TIE);
                }
                else
                {
                    game.switchPlayerTurn();
                }
            }
        }
        
        update();
    }
}

bool ConnectFourWindow::update()
{
    window.clear(sf::Color::Cyan);
    
    sf::RectangleShape backGround( sf::Vector2f(INIT_WIN_X, INIT_WIN_Y) );
    backGround.setFillColor(BackGroundColor);
    window.draw(backGround);
    
    drawBoard();
    drawScoreBox();
    
    if (!game.roundIsWon())
        drawColSelect();
    else
        drawWinText( game.getRoundWinner() );
    
    window.display();
}

