#include "TextureManager.h"
#include <iostream>
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName){
    string path = "images/";
    path+=fileName + ".png";
    //std::cout <<path <<std::endl;
    textures[fileName].loadFromFile(path);
}
sf::Texture& TextureManager::GetTexture(string textureName) {
    if (textures.find(textureName) == textures.end()) {   //invalid iterator
        LoadTexture(textureName);
    }
    return textures[textureName];
}
void TextureManager::Clear() {
    textures.clear();
}