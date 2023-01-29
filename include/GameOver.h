#pragma once
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include "ResourceManager.h"

/*
 * Class for displaying the game over screen, 
 * receives the score from the user, and displays GameOver.
 */

class GameOver
{
public:
  GameOver(const float w_width, const float w_height)
      : m_game_over("GAME OVER", ResourceManager::Resource().getFont(FontIndex::PACMAN), w_height / 7),
        m_game_over_score("", ResourceManager::Resource().getFont(FontIndex::PACMAN), w_height / 15)
  {
    m_game_over.setFillColor(DeepRed);
    m_game_over.setOutlineThickness(6);
    m_game_over.setOutlineColor(sf::Color::White);
    m_game_over.setPosition(w_width / 2, w_height / 3);
    m_game_over.setLetterSpacing(2);
    m_game_over.setOrigin(m_game_over.getGlobalBounds().width / 2, m_game_over.getGlobalBounds().height / 2);

    m_game_over_score.setFillColor(SoftYellow);
    m_game_over_score.setPosition(w_width / 2, w_height / 1.6);
  }

  //-------------------------------------------------------------------
  void setScore(size_t score)
  {
    m_game_over_score.setString("Your Score Is: " + std::to_string(score));
    m_game_over_score.setOrigin(m_game_over_score.getGlobalBounds().width / 2,
                                m_game_over_score.getGlobalBounds().height / 2);
  }

  //-------------------------------------------------------------------
  void draw(sf::RenderWindow& window) const
  {
    while (window.isOpen())
    {
      window.clear(DeepRed);
      window.draw(m_game_over);
      window.draw(m_game_over_score);
      window.display();

      if (auto event = sf::Event{}; window.waitEvent(event))
        if (event.type == sf::Event::Closed)
          window.close();
    }
  }

private:
  sf::Text m_game_over, m_game_over_score;
};
