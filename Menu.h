#include <SFML/Graphics.hpp>
#include <map>
class Menu{
    int mineCount;
    int mineCounter;
    sf::Sprite mineCounterSprite[2] = {};
    sf::Sprite digit1;
    sf::Sprite digit2;
    sf::Sprite digit3;

    sf::Sprite faceUI;
    sf::Sprite debug;
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    void ChangeDigitSprite();
    std::map <std::string, sf::Sprite> buttons;

public:
    Menu(){}
    Menu(int _mineCount, int menuWidth, int menuHeight);
    void DrawMenu(sf::RenderWindow&);
    void RecalculateMineCounter(int flagCount);
    std::map <std::string, sf::Sprite>& GetButtons();
    void ChangeFaceUI(std::string str);
};