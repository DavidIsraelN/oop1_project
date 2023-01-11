#pragma once
#include "Board.h"

enum Type
{
    COOKIE = '*', DEMON = '&', DOOR = 'D', GIFT = '$', KEY = '%', PACMAN = 'a', WALL = '#'
};

class Level
{
public:
	Level();
	~Level();
	void buildLevel(Board&, float, float);
	Object* buildObject(char, int, int) const;  //get char and return pointe to the right object.
	void resetLevel(size_t, size_t);

	void draw(sf::RenderWindow&) const;

	int getRows();
	int getCols();

	// Object* getPacman() {return m_level[21][22];};
private:
	std::vector<std::vector<Object*>> m_level;
	float m_obj_width = 0;
	float m_obj_height = 0;
	size_t m_level_cols = 0;
	size_t m_level_rows = 0;
	sf::Texture m_pacman_texture;
	sf::Texture m_demon_texture;
	sf::Texture m_wall_texture;
	sf::Texture m_door_texture;
	sf::Texture m_gift_texture;
	sf::Texture m_key_texture;
	sf::Texture m_cookie_texture;
};