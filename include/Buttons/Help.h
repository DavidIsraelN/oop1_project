#pragma once
#include "Button.h"
#include <vector>
#include <fstream>

class Help : public Button
{
public:
	Help(sf::Font&, float, float);
	void action(sf::RenderWindow&, Controller&) override;

private:	
	void readHelpTxt();
	void bulidHelpScreen();
	void drawHelp(sf::RenderWindow&) const;

	sf::Font m_font;
	sf::RectangleShape m_help_rect;
	float m_window_width;
	float m_window_height;
	std::ifstream m_help_file;
	std::vector<std::string> m_help_str;
	std::vector<sf::Text> m_help_txt;
};