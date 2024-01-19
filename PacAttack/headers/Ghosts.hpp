#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "Paccy.hpp"

class Ghosts
{
public:
	Ghosts(GHOST);
	void Draw_Ghost(sf::RenderWindow&);
	void set_pos(short, short);
	Position get_pos() const;
	bool pacman_collision(Position) const;
	float get_target_dist(Direction) const;
	void update_target(Direction, Position, Position);
	void update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, Paccy&, Ghosts&);

private:
	GHOST m_Name;

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	Direction m_direction;
	Position m_pos;
	Position m_target;

	int m_XIndex = 0;
	int m_YIndex = 0;
	int m_TextureBit = 16;
};

