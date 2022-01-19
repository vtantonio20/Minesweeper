#include <iostream>
#include "Menu.h"
#include "TextureManager.h"
Menu::Menu(int _mineCount, int menuWidth, int menuHeight){
    mineCount = _mineCount;
    mineCounter = mineCount;
    faceUI.setTexture(TextureManager::GetTexture("face_happy"));
    faceUI.setPosition((menuWidth/2)-32, menuHeight);
    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition((menuWidth-256), menuHeight);
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setPosition((menuWidth-192), menuHeight);
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setPosition((menuWidth-128), menuHeight);
    test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.setPosition((menuWidth-64), menuHeight);

    digit1.setTexture(TextureManager::GetTexture("digits"));
    digit2.setTexture(TextureManager::GetTexture("digits"));
    digit3.setTexture(TextureManager::GetTexture("digits"));

    digit1.setPosition(42, menuHeight);
    digit2.setPosition(21, menuHeight);
    digit3.setPosition(0, menuHeight);

    //std::cout << mineCounter%10 << std::endl;
    digit1.setTextureRect(sf::IntRect(21*(mineCounter%10),0,21,32));
    digit2.setTextureRect(sf::IntRect(21*((mineCounter/10)%10),0,21,32));
    digit3.setTextureRect(sf::IntRect(21*((mineCounter/100)%10),0,21,32));

    buttons.emplace("faceUI", faceUI);
    buttons.emplace("debug" , debug);
    buttons.emplace("test_1", test1);
    buttons.emplace("test_2", test2);
    buttons.emplace("test_3", test3);

}
void Menu::DrawMenu(sf::RenderWindow& window){
    window.draw(faceUI);
    window.draw(debug);
    window.draw(test1);
    window.draw(test2);
    window.draw(test3);

    window.draw(digit1);
    window.draw(digit2);
    window.draw(digit3);

    //std::cout << mineCount << std::endl;

}
void Menu::RecalculateMineCounter(int flagCount) {
    mineCounter=flagCount;
    ChangeDigitSprite();
}

void Menu::ChangeDigitSprite(){
    if(mineCounter>=0){
        digit1.setTextureRect(sf::IntRect(21*(mineCounter%10),0,21,32));
        digit2.setTextureRect(sf::IntRect(21*((mineCounter/10)%10),0,21,32));
        digit3.setTextureRect(sf::IntRect(21*((mineCounter/100)%10),0,21,32));
    }else{
        digit1.setTextureRect(sf::IntRect(21 * (abs(mineCounter) % 10), 0, 21, 32));
        digit2.setTextureRect(sf::IntRect(21*((abs(mineCounter)/10)%10),0,21,32));

        digit3.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
    }
}
std::map <std::string, sf::Sprite>& Menu::GetButtons(){
    return buttons;
}
void Menu::ChangeFaceUI(std::string str) {
    string name = "face_";
    name+=str;
    faceUI.setTexture(TextureManager::GetTexture(name));
}
