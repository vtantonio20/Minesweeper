#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "Tile.h"
#include "Menu.h"
#include "Random.h"
#include "TextureManager.h"

using namespace std;
class Board{
    int cols, rows;
    vector<Tile> tiles;
    int flaggedCount=0;
    int mineCount;
    int mapMineCount;
    Menu menu;
    Tile* GetTilePtr(int x, int y);
    bool WithinBounds(int testNum);
    void ClearBoard();
    void ReadBrd(string fileName);
    void SetNeighbors();
    bool playing;
    bool debug;

public:
    Board();
    Board(int _cols, int _rows, int _mineCount);
    void BuildBoard();
    void DrawBoard(sf::RenderWindow&);
    void TileAction(int x, int y, sf::Event event);
    int GetMineCount(){
        return mineCount;
    }
    void MenuAction(int x, int y);
    void DebugBoard();
    void BuildTestBoard(int testBoardNum);
    vector<sf::Sprite> DebugMines();
    bool Playing(){
        return playing;
    }
};