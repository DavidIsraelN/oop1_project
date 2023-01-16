#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

class ResourceManage
{
public:
  static ResourceManage* Instance();

  sf::Font* getFont() { return &m_font; }

  std::ifstream* getHelpFile() { return &m_help_file; }
  std::ifstream* getBoard1()   { return &m_board_1;   }
  std::ifstream* getBoard2()   { return &m_board_2;   }
  std::ifstream* getBoard3()   { return &m_board_3;   }

  sf::Texture* getPacmanT() { return &m_pacman_texture; }
  sf::Texture* getDemonT()  { return &m_demon_texture;  }
  sf::Texture* getWallT()   { return &m_wall_texture;   }
  sf::Texture* getDoorT()   { return &m_door_texture;   }
  sf::Texture* getGiftT()   { return &m_gift_texture;   }
  sf::Texture* getKeyT()    { return &m_key_texture;    }
  sf::Texture* getCookieT() { return &m_cookie_texture; }

  sf::SoundBuffer* getGameStart() { return &m_game_start; }
  sf::SoundBuffer* getEatCookie() { return &m_eat_cookie; }
  sf::SoundBuffer* getEatGift() { return &m_eat_gift; }
  sf::Image* getIcon() { return &m_icon; }

private:
  ResourceManage();

  static ResourceManage* m_instance;
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

  sf::Image m_icon;

  //music too
  sf::SoundBuffer m_game_start;
  sf::SoundBuffer m_eat_cookie;
  sf::SoundBuffer m_eat_gift;
};

//ResourceManage* ResourceManage::m_instance = nullptr;