#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "GhostManager.hpp"


class Paccy
{
public:
	Paccy();
	void Draw_Paccy(sf::RenderWindow&);
	void set_pos(short, short);
	Position get_pos() const;
	Direction get_dir() const;
	void update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, GhostManager&);
	void set_dead(bool);
	bool get_dead() const;

private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	bool m_dead;

	Direction m_direction;
	Position m_pos;
	unsigned char energizer_timer;

	int m_XIndex = 0;
	int m_YIndex = 0;
	int m_TextureBit = 16;
};

