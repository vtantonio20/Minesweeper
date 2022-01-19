#include "Board.h"

Board::Board(){
}
Board::Board(int _cols, int _rows,int _mineCount){
    cols =_cols;
    rows = _rows;
    vector<Tile> tiles ={};

    flaggedCount=0;
    mapMineCount=_mineCount;
    mineCount = _mineCount;
    menu =Menu(mineCount, (cols*32), (rows*32));
    playing = true;
    debug = false;
}
void Board::ClearBoard() {
    tiles ={};
    flaggedCount=0;
    menu.RecalculateMineCounter(mineCount);


}
Tile* Board::GetTilePtr(int x, int y) {

    if(x<1 || x >= cols){
        return nullptr;
    }
    if(y<1 || y>= rows){
        return nullptr;
    }
    for(int i=0; i < tiles.size(); i++){
        if(tiles[i].GetX() == x && tiles[i].GetY() == y){
            cout << "found" << endl;
            Tile* tilePtr = &tiles[i];
            return tilePtr;
        }
    }
    cout << "end reached" << endl;
    return nullptr;
}
void Board::SetNeighbors() {
    //This sets neighbors up
    for(int i =0; i < tiles.size(); i++){
        int x = tiles[i].GetX();
        int y = tiles[i].GetY();
        Tile* tilePtr[8];
        for (int i=0; i < 8; i++)
            tilePtr[i] = &tiles[i];

        if(x==1){
            tilePtr[0] = nullptr;
            tilePtr[7] = nullptr;
            tilePtr[6] = nullptr;
        }else if(x == cols){
            tilePtr[2] = nullptr;
            tilePtr[3] = nullptr;
            tilePtr[4] = nullptr;
        }
        if(y == 1){
            tilePtr[0] = nullptr;
            tilePtr[1] = nullptr;
            tilePtr[2] = nullptr;
        }else if(y == rows){
            tilePtr[4] = nullptr;
            tilePtr[5] = nullptr;
            tilePtr[6] = nullptr;
        }
        for (int j=0; j < 8; j++){
            if(tilePtr[j] != nullptr){
                int adjPosition;
                switch(j){
                    case 0:{adjPosition = i-cols-1; break;}
                    case 1:{ adjPosition= i-cols;   break;}
                    case 2:{ adjPosition= i-cols+1; break;}
                    case 3:{ adjPosition= i+1;      break;}//
                    case 4:{ adjPosition= i+cols+1; break;}
                    case 5:{ adjPosition= i+cols;   break;}
                    case 6:{ adjPosition= i+cols-1; break;}
                    case 7:{ adjPosition= i-1;      break;}
                }
                tilePtr[j] = &tiles[adjPosition];
            }

        }
        for(int k=0; k <8; k++){
            tiles[i].AddAdjacentTile(k,tilePtr[k]);
        }
        tiles[i].UpdateAdjacentMineCount();
    }
}
void Board::BuildBoard() {
    int xOffset = 0;
    int yOffset =0;
    for (int i =0; i < rows; i++){
        for(int j =0; j < cols; j++){
            tiles.push_back(Tile(xOffset, yOffset));
            xOffset+=32;
        }
        xOffset=0;
        yOffset+=32;
    }
    int deployedMineCount = 0;
    //deploys random mines
    while(deployedMineCount< mineCount){
        int randIndex = Random::Int(0,tiles.size());
        if(tiles[randIndex].IsMine() == false){
            tiles[randIndex].ChangeToMine();
            deployedMineCount++;
        }
    }

    //This sets neighbors up
    SetNeighbors();
}
void Board::DrawBoard(sf::RenderWindow& window){
    //draw playable tiles
    for(int i =0; i < tiles.size(); i++){
        tiles[i].DrawTile(window);
    }

    menu.DrawMenu(window);
    //draw menu
}
void Board::TileAction(int x, int y, sf::Event event){
    int mouseRow = (x/32)+1;
    int mouseCol = (y/32)+1;
    //cout<< mouseRow<<  "\t"<< mouseCol <<endl;
    int count=0;
    int revealedCount=0;


    for (int i =0; i < rows; i++){
        for(int j =0; j < cols; j++){
            if(tiles[count].VerifyPos(mouseRow,mouseCol)){
                Tile& clickedTile = tiles[count];
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(clickedTile.IsFlagged() == false && (clickedTile.IsHidden())){
                        clickedTile.ToggleHidden();
                        if(clickedTile.IsMine() == false){
                            if(clickedTile.GetAdjMineCount() ==0){
                                clickedTile.RecursiveReveal(&clickedTile, cols, rows);
                            }
                            for(int k=0; k < tiles.size(); k++){
                                if(tiles[k].IsHidden()==false && tiles[k].IsMine()== false)
                                    revealedCount++;
                            }
                            if(revealedCount== (rows*cols)-mineCount) {
                                cout << "Winner!" << endl;
                                flaggedCount=0;
                                for(int k=0; k < tiles.size(); k++){
                                    if(tiles[k].IsMine() && tiles[k].IsFlagged() ==false){
                                        tiles[k].ToggleFlag();
                                        flaggedCount++;
                                    }
                                }
                                menu.RecalculateMineCounter(0);
                                menu.ChangeFaceUI("win");
                                playing = false;
                                return;
                            }
                        }else {
                            //GAMEOVER!
                            cout << "Game Over" << endl;
                            menu.ChangeFaceUI("lose");
                            for (int k=0; k < tiles.size(); k++){
                                if(tiles[k].IsMine() && &tiles[k] != &clickedTile){
                                    tiles[k].ToggleHidden();
                                }
                            }
                            playing = false;
                            return;
                        }


                    }else{
                        cout << "no effect for left click tile is flagged or is already unhidden" << endl;
                    }
                }else if(event.mouseButton.button == sf::Mouse::Right){
                    if(clickedTile.IsHidden() || debug ==true){
                        if(clickedTile.IsFlagged())
                            flaggedCount--;
                        else
                            flaggedCount++;
                        menu.RecalculateMineCounter(mineCount-flaggedCount);
                        clickedTile.ToggleFlag();
                    }else{
                        cout << "no effect for right click tile is already unhidden" << endl;
                    }
                }
                return;
            }else
                count++;
        }
    }
}
void Board::MenuAction(int x, int y) {
    map <std::string, sf::Sprite>& buttons = menu.GetButtons();
    auto iter = buttons.begin();

    for (; iter != buttons.end(); ++iter){
        if(iter->second.getPosition().x+iter->second.getTextureRect().width >=x && x >=iter->second.getPosition().x){
            if(iter->first == "faceUI"){
                mineCount = mapMineCount;
                ClearBoard();
                BuildBoard();
                menu.ChangeFaceUI("happy");
                playing = true;
            }else if(iter->first =="debug"){
                if(playing){
                    for (int k=0; k < tiles.size(); k++){
                        if(tiles[k].IsMine()){
                            tiles[k].ToggleHidden();
                        }
                    }
                    if(debug)
                        debug=false;
                    else
                        debug=true;
                }
            }else if(iter->first =="test_1"){
                BuildTestBoard(1);
                menu.ChangeFaceUI("happy");
                playing = true;
            }else if(iter->first =="test_2"){
                BuildTestBoard(2);
                menu.ChangeFaceUI("happy");
                playing = true;
            }else if(iter->first =="test_3"){
                BuildTestBoard(3);
                menu.ChangeFaceUI("happy");
                playing = true;
            }

        }
    }
}
//BROCKEN
vector <sf::Sprite> Board::DebugMines() {
    vector<sf::Sprite> dMines;
    for(int i=0; i < tiles.size(); i++){
        if(tiles[i].IsMine()){
            sf::Sprite mSprite;
            mSprite.setPosition(tiles[i].GetSprite().getPosition());
            mSprite.setTexture(TextureManager::GetTexture("mine"));
            dMines.push_back(mSprite);
        }
    }
    return dMines;
}

void Board::BuildTestBoard(int testBoardNum) {
    switch(testBoardNum){
        case 1:
            ReadBrd("boards/testboard1.brd");
            break;
        case 2:
            ReadBrd("boards/testboard2.brd");
            break;
        case 3:
            ReadBrd("boards/testboard3.brd");
            break;
        case 4:
            ReadBrd("boards/lots_o_mines.brd");
            break;
        case 5:
            ReadBrd("boards/recursion_test.brd");
            break;
    }
}

void Board::ReadBrd(string fileName) {
    ClearBoard();
    ifstream file(fileName);
    if (file.is_open()){
        cols=25;
        rows=16;
        char tBD[400];
        int mC =0;
        for(int i=0; i < 400; i++){
            char num;
            file >> num;
            tBD[i] = num;
        }
        int xOffset = 0;
        int yOffset =0;
        int count=0;
        //tBD[0] = '0';
        for (int i =0; i < rows; i++){
            for(int j =0; j < cols; j++){
                if(tBD[count]== '0'){
                    tiles.push_back(Tile(xOffset, yOffset, false));
                }
                else if(tBD[count]== '1'){
                    //cout << "is mine" << endl;
                    tiles.push_back(Tile(xOffset, yOffset, true));
                    mC++;
                }
                xOffset+=32;
                count++;
            }
            xOffset=0;
            yOffset+=32;
            mineCount=mC;
            menu.RecalculateMineCounter(mineCount);
            SetNeighbors();
        }
    }else{
        cout << "file not found" << endl;
    }
}
