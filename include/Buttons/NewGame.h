#pragma once
#include "Button.h"
#include "../Colors.h"

//class Button;

class NewGame : public Button
{
public:
    NewGame(sf::Font& font, float width, float height) 
      : Button("New Game", font, { width / 2 , height / 4 }, height / 30, SoftYellow) { }

    void action(sf::RenderWindow& window) override { }

};