#pragma once
#include "Button.h"
#include <vector>
//#include "ChooseLevel.h"

class NewGame : public Button
{
public:
  NewGame(sf::Font&, float, float);
  void action(sf::RenderWindow&) override;

private:
  void selectLevel(sf::RenderWindow&) const;
  void drawLevels(sf::RenderWindow&) const;


  std::vector<Button*> m_levels;

  //ChooseLevel m_levels;
};