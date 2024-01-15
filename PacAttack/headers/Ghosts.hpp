#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"

class Ghosts
{
public:
	// Ghosts();
	void Draw_Ghost(sf::RenderWindow&);
	void set_pos(short, short);
	void update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&);

private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	Direction m_direction;
	Position m_pos;

	int m_XIndex = 0;
	int m_YIndex = 0;
	int m_TextureBit = 16;
};

