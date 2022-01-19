#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Window.h"
using namespace std;

Window::Window(string configPath){
    ifstream file(configPath);
    if (file.is_open()){
        string line;

        getline(file, line);
        cols = stoi(line);
        getline(file, line);
        rows = stoi(line);
        getline(file, line);
        mineCount = stoi(line);

    }else{
        cout << "file not found" << endl;
    }

}
int Window::GetCols(){
    return cols;
}
int Window::GetRows(){
    return rows;
}
int Window::GetWidth() {
    return cols *32;
}
int Window::GetHeight() {
    return (rows *32)+88;
}
int Window::GetMineCount(){
    return mineCount;
}