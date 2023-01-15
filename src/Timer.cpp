#include "Timer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Timer::Timer(sf::Font& font)
{
  m_text.setFont(font);
  m_text.setPosition(400, 810);
  m_text.setCharacterSize(30);
  m_text.setFillColor(sf::Color::White);
}

void Timer::draw(sf::RenderWindow & window) const
{
  window.draw(m_text);
}

void Timer::setTimer(int elapsed)
{
  m_time_left = m_time_start - elapsed;

  int minutes = static_cast<int>(m_time_left) / 60 % 60;
  int seconds = static_cast<int>(m_time_left) % 60;

  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << minutes << ":"
     << std::setfill('0') << std::setw(2) << seconds;
  m_text.setString(ss.str());
  m_text.setOrigin(m_text.getLocalBounds().width / 2, 0);

  if(m_time_left <= 30)
    m_text.setFillColor(sf::Color::Red);
}

void Timer::setStart(int board_num)
{
  switch (board_num)
  {
    case 1:
      m_time_start = 2 * 60;
      break;
    case 2:
      m_time_start = 3 * 60;
      break;
    case 3:
      m_time_start = 4 * 60;
      break;
  }
}

void Timer::addTime(int add)
{
  m_time_start += add;
}