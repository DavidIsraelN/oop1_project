#include "ResourceManage.h"

ResourceManage* ResourceManage::Resource()
{
  static ResourceManage m_instance;
  return &m_instance;
}

ResourceManage::ResourceManage()
    : m_help_file(std::ifstream("Help.txt")),
      m_board_1(std::ifstream("Level_1.txt")),
      m_board_2(std::ifstream("Level_2.txt")),
      m_board_3(std::ifstream("Level_3.txt"))
{
  m_font.loadFromFile("Arial.ttf");
  m_pacman_texture.loadFromFile("pacman.png");
  m_super_pacman_texture.loadFromFile("super_pacman.png");
  m_demon_texture.loadFromFile("demon.png");
  m_wall_texture.loadFromFile("wall.jpg");
  m_door_texture.loadFromFile("door.png");
  m_gift_texture.loadFromFile("gift.png");
  m_key_texture.loadFromFile("key.png");
  m_cookie_texture.loadFromFile("cookie.png");
  m_game_start.loadFromFile("game_start.wav");
  m_eat_cookie.loadFromFile("credit.wav");
  m_eat_gift.loadFromFile("eat_fruit.wav");
  m_icon.loadFromFile("pacman.png");

}

//
//ResourceManage::ResourceManage()
//	: m_help_file(std::ifstream("Help.txt")),
//	m_board_1(std::ifstream("Level_1.txt")),
//	m_board_2(std::ifstream("Level_2.txt")),
//	m_board_3(std::ifstream("Level_3.txt"))
//{
//	m_font.loadFromFile("Arial.ttf");
//	m_pacman_texture.loadFromFile("pacman.png");
//	m_demon_texture.loadFromFile("demon.png");
//	m_wall_texture.loadFromFile("wall.jpg");
//	m_door_texture.loadFromFile("door.png");
//	m_gift_texture.loadFromFile("gift.png");
//	m_key_texture.loadFromFile("key.png");
//	m_cookie_texture.loadFromFile("cookie.png");
//}
//
//sf::Font ResourceManage::getFont() const { return m_font; }
//
//const std::ifstream* ResourceManage::getHelpFile() const { return &m_help_file; }
//const std::ifstream* ResourceManage::getBoard1() const { return &m_board_1; }
//const std::ifstream* ResourceManage::getBoard2() const { return &m_board_2; }
//const std::ifstream* ResourceManage::getBoard3() const { return &m_board_3; }
//
//sf::Texture ResourceManage::getPacmanT() const { return m_pacman_texture; }
//sf::Texture ResourceManage::getDemonT() const { return m_demon_texture; }
//sf::Texture ResourceManage::getWallT() const { return m_wall_texture; }
//sf::Texture ResourceManage::getDoorT() const { return m_door_texture; }
//sf::Texture ResourceManage::getGiftT() const { return m_gift_texture; }
//sf::Texture ResourceManage::getKeyT() const { return m_key_texture; }
//sf::Texture ResourceManage::getCookieT() const { return m_cookie_texture; }
