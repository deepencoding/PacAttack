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
	void switch_mode();
	bool pacman_collision(Position) const;
	float get_target_dist(Direction) const;
	void reset_ghost(Position, Position);
	void update_target(Direction, Position, Position);
	void update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, Paccy&, Ghosts&);

private:
	GHOST m_Name;
	MODE m_mode;
	bool isFrightened;
	bool use_door;

	std::array<Position, 4> restricted_cells = {
		Position(CELL_SIZE * 9, CELL_SIZE * 7) ,
		Position(CELL_SIZE * 11, CELL_SIZE * 7),
		Position(CELL_SIZE * 9, CELL_SIZE * 15),
		Position(CELL_SIZE * 11, CELL_SIZE * 15)
		};

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	Direction m_direction;
	Position m_pos;
	Position m_target;
	Position m_house;
	Position m_gate;

	int m_XIndex = 0;
	int m_YIndex = 0;
	int m_TextureBit = 16;
};

