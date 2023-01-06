#include "Buttons/Help.h"
#include "Colors.h"
#include <thread>

Help::Help(sf::Font& font, float width, float height) : m_font(font),
  Button("Help", font, { width / 2 , height / 2 }, height / 30, SoftYellow), 
	m_help_file(std::ifstream("Help.txt")), 
  m_window_width(width), m_window_height(height) 
{
  readHelpTxt();
  bulidHelpScreen();
}


void Help::action(sf::RenderWindow& window) 
{
  drawHelp(window);
}

void Help::readHelpTxt()
{
  std::string line;
  m_help_str.clear();
  while(std::getline(m_help_file, line))
    m_help_str.push_back(line);
}

void Help::bulidHelpScreen()
{
  for (size_t i = 0; i < m_help_str.size(); ++i)
  {
    if (m_help_str[i].empty())
      continue;

    auto div = (i < m_help_str.size() / 2) ? m_help_str.size() - i : 1 / m_help_str.size() - i;
    auto line = sf::Text(m_help_str[i], m_font);
    line.setFillColor(Gray);
    line.setCharacterSize(m_window_width / m_help_str.size());
    line.setPosition({m_window_width / 2, m_window_height / div});
    const auto rect = line.getLocalBounds();
    //m_text.setScale(width / rect.width / scale, height / rect.height / scale);
    line.setOrigin(rect.width / 2, rect.height / 2);
    m_help_txt.push_back(line);
  }
}

void Help::drawHelp(sf::RenderWindow& window) const
{
  window.clear(SoftYellow);
  for (auto i = size_t(0); i < m_help_txt.size(); ++i)
    window.draw(m_help_txt[i]);
  window.display();
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(5s); // wait 3 seconds
}
