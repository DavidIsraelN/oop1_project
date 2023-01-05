#include "Level.h"

Level::Level()
{
    m_pacman_texture.loadFromFile("pacman.png");
    m_demon_texture.loadFromFile("demon.png");
    m_wall_texture.loadFromFile("wall.jpg");
    m_door_texture.loadFromFile("door.png");
    m_gift_texture.loadFromFile("gift.png");
    m_key_texture.loadFromFile("key.png");
    m_cookie_texture.loadFromFile("cookie.png");
}

void Level::buildLevel(Board& board)
{
    board.setCurrentLevel();

    m_level.resize(board.getVector().size());
    for (auto i = size_t(0); i < m_level.size(); ++i)
        m_level[i].resize(board.getVector()[i].size(), nullptr);


    for (int i = 0; i < board.getVector().size(); ++i)
        for (int j = 0; j < board.getVector()[i].size(); ++j)
                m_level[i][j] = buildObject(board.getVector()[i][j], i, j);
}

Object* Level::buildObject(char c, int i, int j) const
{
    switch (c)
    {
        case 'a':
            return new Pacman(m_pacman_texture,{PIXELS * j + PIXELS / 2,  PIXELS * i + PIXELS / 2});
        case '&':
            return new Demon(m_demon_texture,{PIXELS * j + PIXELS / 2,  PIXELS * i + PIXELS / 2});
        case '*':
            return new Cookie(m_cookie_texture,{PIXELS * j + PIXELS / 2,  PIXELS * i + PIXELS / 2});
        case '$':
            return new Gift(m_gift_texture,{PIXELS * j + PIXELS / 2,  PIXELS * i + PIXELS / 2});
        case 'D':
            return new Door(m_door_texture,{PIXELS * j + PIXELS / 2,  PIXELS * i + PIXELS / 2});
        case '%':
            return new Key(m_key_texture,{PIXELS * j + PIXELS / 2,  PIXELS * i + PIXELS / 2});
        case '#':
            return new Wall(m_wall_texture,{PIXELS * j + PIXELS / 2,  PIXELS * i + PIXELS / 2});
    }
    return nullptr;
}

int Level::getRows() {
    return m_level.size();
}

int Level::getCols() {
    return m_level[0].size();
}

void Level::draw(sf::RenderWindow& window) const
{
        for (auto i = size_t(0); i < m_level.size(); ++i)
            for (auto j = size_t(0); j < m_level[i].size(); ++j)
            {
                if (!m_level[i][j]) continue;
                m_level[i][j]->draw(window);
            }
}