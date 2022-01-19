#include "Tile.h"

#include "TextureManager.h"
Tile::Tile(){
}
Tile::Tile(int xPos, int yPos, bool _isMine){
    pos = sf::Vector2f(xPos, yPos);
    tileSprite.setPosition(pos);
    row = (xPos/32)+1;
    col= (yPos/32)+1;
    isFlagged = false;
    isMine = _isMine;
    hidden = true;
    adjacentMines=0;
    for(int i=0; i < 8; i++)
        adjTiles[i] = nullptr;

}
sf::Sprite& Tile::GetSprite() {
    if(hidden == true)
        tileSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
    else
        tileSprite.setTexture(TextureManager::GetTexture("tile_revealed"));
    return tileSprite;
}

bool Tile::VerifyPos(int otherRow, int otherCol){
    if(otherRow == row && otherCol == col)
        return true;
    else
        return false;

}
void Tile::ToggleFlag() {
    if(isFlagged == true)
        isFlagged = false;
    else
        isFlagged = true;
}
bool Tile::IsFlagged(){
    return isFlagged;
}


void Tile::ChangeToMine() {
    isMine = true;
}
bool Tile::IsMine(){
    if (isMine == true)
        return true;
    else
        return false;
}


bool Tile::IsHidden(){
    if (hidden == true)
        return true;
    else
        return false;
}
void Tile::ToggleHidden(){
    if(hidden == true)
        hidden = false;
    else
        hidden = true;
}
//Only call this in build board
void Tile::AddAdjacentTile(int index, Tile* tile){
    adjTiles[index] = tile;
}

const int Tile::GetX() {
    return row;

}
const int Tile::GetY() {
    return col;
}

void Tile::PrintAdjacentLocations() {
    for(int i=0; i < 8; i++){
        if(adjTiles[i]==nullptr){
            cout << "null tile at: " << i << endl;
        }else{
            cout <<i << "\tX: "<< adjTiles[i]->GetX() << "\tY:" << adjTiles[i]->GetY() << endl;
        }
    }
    cout <<"\n";
}
//Only call this in build board
void Tile::UpdateAdjacentMineCount() {
    adjacentMines=0;
    for (int i =0; i < 8; i++){
        if(adjTiles[i] != nullptr && adjTiles[i]->IsMine() == true){
            adjacentMines++;
            if(adjacentMines>8){
                cout << "sum ting go wong" << endl;
            }
        }
    }
    if(adjacentMines!=0){
        string num = "number_";
        num+=to_string(adjacentMines);
    }
}

void Tile::DrawTile(sf::RenderWindow& window){
    window.draw(GetSprite());
    if(hidden){
        if(isFlagged){
            sf::Sprite fSprite;
            fSprite.setPosition(pos);
            fSprite.setTexture(TextureManager::GetTexture("flag"));
            window.draw(fSprite);
        }
    }else if(isMine){
        if(isFlagged){
            sf::Sprite fSprite;
            fSprite.setPosition(pos);
            fSprite.setTexture(TextureManager::GetTexture("flag"));
            window.draw(fSprite);
        }
        sf::Sprite mSprite;
        mSprite.setPosition(pos);
        mSprite.setTexture(TextureManager::GetTexture("mine"));
        window.draw(mSprite);
    }else if(adjacentMines!=0){
        //display digit
        sf::Sprite dSprite;
        dSprite.setPosition(pos);

        string num = "number_";
        num+=to_string(adjacentMines);
        dSprite.setTexture(TextureManager::GetTexture(num));
        window.draw(dSprite);
    }
}

void Tile::RecursiveReveal(Tile* clickedTile, int cols, int rows) {
    vector<Tile*> tilesWithNoAdjMines;
    for(int i=0; i < 8; i++){
        if(clickedTile->adjTiles[i] != nullptr){
            if(clickedTile->adjTiles[i]->IsHidden() == true && clickedTile->adjTiles[i]->IsFlagged() == false){
                clickedTile->adjTiles[i]->ToggleHidden();
                if(clickedTile->adjTiles[i]->GetAdjMineCount() == 0 )
                    tilesWithNoAdjMines.push_back(clickedTile->adjTiles[i]);
            }
        }
    }
    for(int i=0; i < tilesWithNoAdjMines.size(); i++){
        RecursiveReveal(tilesWithNoAdjMines[i], cols, rows);
    }
}
int Tile::GetAdjMineCount() {
    return adjacentMines;
}

