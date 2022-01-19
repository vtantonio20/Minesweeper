#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Board.h"

//#include "Tile.h"
int main()
{
    Window win = Window("boards/config.cfg");
    const int windowHeight = win.GetHeight();
    const int windowWidth = win.GetWidth();

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper!");
    Board board = Board(win.GetCols(), win.GetRows(), win.GetMineCount());
    board.BuildBoard();


    while(window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();


            if(event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i position = sf::Mouse::getPosition(window);

                if (position.y < windowHeight - 88) {
                    if(board.Playing())
                        board.TileAction(position.x, position.y, event);
                }else{
                    if(event.mouseButton.button == sf::Mouse::Left && position.y < windowHeight-88+64){
                        board.MenuAction(position.x, position.y);
                    }
                }
            }

        }

        window.clear(sf::Color(255,255,255,255));
        board.DrawBoard(window);
        window.display();
    }

    //clea
    TextureManager::Clear();
    return 0;
}