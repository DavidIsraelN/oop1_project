#pragma once
#include <SFML/Graphics.hpp>
class FontLoader
{
public:
    FontLoader() {m_font.loadFromFile("Arial.ttf");}
    sf::Font getFont() {return m_font;}
private:
    sf::Font m_font;
};