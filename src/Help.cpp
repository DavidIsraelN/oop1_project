#include "Buttons/Help.h"
#include "Colors.h"

Help::Help(sf::Font& font, std::ifstream* help_file, float width, float height) : m_font(font),
  Button("Help", font, { width / 2 , height / 2 }, height / 30, SoftYellow),
  m_back(font, { width - 50 , 30 }, height / 45),
	m_help_file(help_file), m_help_rect({width, height}),
  m_window_width(width), m_window_height(height) 
{
  readHelpTxt();
  bulidHelpScreen();
}

bool Help::action(sf::RenderWindow& window, Controller& c)
{
  drawHelp(window);
  while (window.isOpen())
  {
    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        if (m_back.clickMe(loc))
          return m_back.action(window, c);
      }
  }
  return false;
}

void Help::readHelpTxt()
{
  std::string line;
  m_help_str.clear();
  while(std::getline(*m_help_file, line))
    m_help_str.push_back(line);
}

void Help::bulidHelpScreen()
{
  m_help_rect.setFillColor(SemiSoftYellow);
  auto line_height = m_window_width / m_help_str.size();
  //m_help_txt.push_back(sf::Text("< Back", m_font, m_window_height / 45));
  //m_help_txt[0].setFillColor(sf::Color::White);
  //m_help_txt[0].setPosition({ m_window_width - 50 , 30 });
  //m_help_txt[0].setOrigin(m_help_txt[0].getLocalBounds().width / 2,
  //                        m_help_txt[0].getLocalBounds().height / 2);
  for (auto i = size_t(0); i < m_help_str.size(); ++i)
  {
    if (m_help_str[i].empty())
      continue;
    auto line = sf::Text(m_help_str[i], m_font, (m_help_txt.size() == 0)? line_height : line_height / 1.5);
    line.setFillColor(DeepRed);
    line.setPosition({m_window_width / 2, line_height * i});
    line.setOrigin(line.getLocalBounds().width / 2, line.getLocalBounds().height / 2);
    m_help_txt.push_back(line);
  }

  if (m_help_txt.size() < 1) return;
  m_help_txt[0].setStyle(sf::Text::Underlined);
}

void Help::drawHelp(sf::RenderWindow& window) const
{
  window.clear(DeepRed);
  window.draw(m_help_rect);
  m_back.draw(window);
  for (auto i = size_t(0); i < m_help_txt.size(); ++i)
    window.draw(m_help_txt[i]);
  window.display();
}
