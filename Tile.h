#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Tile{
    int row;
    int col;
    sf::Vector2f pos;
    sf::Sprite tileSprite;

    bool isFlagged;
    bool isMine;
    bool hidden;

    int adjacentMines=0;
    Tile* adjTiles[8];
public:

    Tile();

    Tile(int xPos, int yPos, bool _isMine=false);
    sf::Sprite& GetSprite();
    bool VerifyPos(int otherRow, int otherCol);
    bool IsFlagged();
    void ToggleFlag();
    void ChangeToMine();
    bool IsMine();
    bool IsHidden();
    void ToggleHidden();
    void AddAdjacentTile(int index, Tile* tile);
    const int GetX();
    const int GetY();
    void PrintAdjacentLocations();
    void UpdateAdjacentMineCount();
    void DrawTile(sf::RenderWindow& window);
    int GetAdjMineCount();

    void RecursiveReveal(Tile* clickedTile, int maxCols, int maxRows);

};