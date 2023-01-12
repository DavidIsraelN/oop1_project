#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

class ResourceManage
{
public:
	/*ResourceManage();
	sf::Font getFont() const;
	const std::ifstream* getHelpFile() const;
	const std::ifstream* getBoard1() const;
	const std::ifstream* getBoard2() const;
	const std::ifstream* getBoard3() const;*/
	ResourceManage()
		: m_help_file(std::ifstream("Help.txt")),
		m_board_1(std::ifstream("Level_1.txt")),
		m_board_2(std::ifstream("Level_2.txt")),
		m_board_3(std::ifstream("Level_3.txt"))
	{
		m_font.loadFromFile("Arial.ttf");
		m_pacman_texture.loadFromFile("pacman.png");
		m_demon_texture.loadFromFile("demon.png");
		m_wall_texture.loadFromFile("wall.jpg");
		m_door_texture.loadFromFile("door.png");
		m_gift_texture.loadFromFile("gift.png");
		m_key_texture.loadFromFile("key.png");
		m_cookie_texture.loadFromFile("cookie.png");
		m_rekaa.loadFromFile("game_start.wav");
	}

	sf::Font getFont() const { return m_font; }

	std::ifstream* getHelpFile() { return &m_help_file; }
	std::ifstream* getBoard1()   { return &m_board_1;   }
	std::ifstream* getBoard2()   { return &m_board_2;   }
	std::ifstream* getBoard3()   { return &m_board_3;   }

	sf::Texture* getPacmanT() { return &m_pacman_texture; }
	sf::Texture* getDemonT()  { return &m_demon_texture;  }
	sf::Texture* getWallT()   { return &m_wall_texture;   }
	sf::Texture* getDoorT()   { return &m_door_texture;   }
	sf::Texture* getGiftT()   { return &m_gift_texture;   }
	sf::Texture* getkeyT()    { return &m_key_texture;    }
	sf::Texture* getCookieT() { return &m_cookie_texture; }

	sf::SoundBuffer* getReka() { return &m_rekaa; }

private:
	sf::Font m_font;

	sf::Texture m_pacman_texture;
	sf::Texture m_demon_texture;
	sf::Texture m_wall_texture;
	sf::Texture m_door_texture;
	sf::Texture m_gift_texture;
	sf::Texture m_key_texture;
	sf::Texture m_cookie_texture;

	std::ifstream m_board_1;
	std::ifstream m_board_2;
	std::ifstream m_board_3;
	std::ifstream m_help_file;

	//music too
	sf::SoundBuffer m_rekaa;
	sf::Music m_reka;
};