#pragma once
#include "Board.h"
#include "Objects/Object.h"
#include <memory>

enum ObjType
{
	COOKIE = '*', DEMON = '&', DOOR = 'D',
	GIFT   = '$', KEY   = '%', PACMAN = 'a',
	WALL   = '#', SPACE = ' '
};

class Level
{
public:
	//Level();
	//~Level();
	void buildLevel(Board&, ResourceManage&, float, float);
	//Object* buildObject(char, size_t, size_t) const;  //get char and return pointe to the right object.
	std::unique_ptr<Object> createObject(ObjType, ResourceManage&, size_t, size_t) const;
	//void resetLevel(size_t, size_t);

	void draw(sf::RenderWindow&) const;

	int getRows();
	int getCols();

	// Object* getPacman() {return m_level[21][22];};
private:
	std::vector<std::unique_ptr<Object>> m_level;
	float m_obj_width = 0;
	float m_obj_height = 0;
	size_t m_level_cols = 0;
	size_t m_level_rows = 0;

	//sf::Texture m_pacman_texture;
	//sf::Texture m_demon_texture;
	//sf::Texture m_wall_texture;
	//sf::Texture m_door_texture;
	//sf::Texture m_gift_texture;
	//sf::Texture m_key_texture;
	//sf::Texture m_cookie_texture;
};