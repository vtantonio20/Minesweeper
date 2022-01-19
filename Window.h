#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Window{
    int cols, rows, mineCount;
public:
    Window(string configPath);
    int GetWidth();
    int GetHeight();
    int GetCols();
    int GetRows();
    int GetMineCount();
};
