#pragma once
//#include "Board.h"
#include "Objects/Object.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>

enum ObjType
{
	COOKIE = '*', DEMON = '&', DOOR = 'D',
	GIFT   = '$', KEY   = '%', PACMAN = 'a',
	WALL   = '#', SPACE = ' '
};

class ResourceManage;

class Level
{
public:
	//Level();
	//~Level();
  //void resetLevel(size_t, size_t);
	//Object* createObject(ObjType, ResourceManage&, size_t, size_t) const;//get char and return pointe to the right object.

	void buildLevel(ResourceManage&, float, float);
	std::unique_ptr<Object> createObject(ObjType, ResourceManage&, size_t, size_t) const;
	void draw(sf::RenderWindow&) const;
	void setCurrentLevel(ResourceManage&, size_t);
	void chooseBoard(ResourceManage& resource, size_t);
	size_t getRows() const;
	size_t getCols() const;

private:
	std::ifstream* m_current_board = nullptr;
	std::vector<std::string> m_level_txt;
	std::vector<std::unique_ptr<Object>> m_level;
	float m_obj_width = 0;
	float m_obj_height = 0;
	size_t m_level_cols = 0;
	size_t m_level_rows = 0;

	//std::vector<Object*> m_level;
	//sf::Texture m_pacman_texture;
	//sf::Texture m_demon_texture;
	//sf::Texture m_wall_texture;
	//sf::Texture m_door_texture;
	//sf::Texture m_gift_texture;
	//sf::Texture m_key_texture;
	//sf::Texture m_cookie_texture;
};