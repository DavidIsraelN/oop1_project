#pragma once
#include "Board.h"


class Level
{
public:
    Level();
    void buildLevel(Board&);
    Object* buildObject(char, int ,int) const;       //get char and return pointe to the right object.

    void draw(sf::RenderWindow&) const;

    int getRows();
    int getCols();

   // Object* getPacman() {return m_level[21][22];};
private:
    std::vector<std::vector<Object*>> m_level;


    sf::Texture m_pacman_texture;
    sf::Texture m_demon_texture;
    sf::Texture m_wall_texture;
    sf::Texture m_door_texture;
    sf::Texture m_gift_texture;
    sf::Texture m_key_texture;
    sf::Texture m_cookie_texture;
};