#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "global.hpp"

class Paccy;

class Ghosts
{
public:
	Ghosts(GHOST);
	void Draw_Ghost(bool, sf::RenderWindow&);
	void set_pos(short, short);
	Position get_pos() const;
	GHOST get_name() const;
	void switch_mode();
	void switch_frightened();
	bool pacman_collision(Position) const;
	float get_target_dist(Direction) const;
	MODE get_mode() const;
	void reset_ghost(Position, Position);
	void update_target(Direction, Position, Position);
	void update(unsigned char, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, Paccy&, Ghosts&);

private:
	GHOST m_Name;
	MODE m_mode;
	FRIGHT isFrightened;
	int fright_speed_timer;
	int tunnel_speed_timer;
	int animation_timer;
	bool use_door;

	std::array<Position, 4> restricted_cells = {
		Position(CELL_SIZE * 9, CELL_SIZE * 7) ,
		Position(CELL_SIZE * 11, CELL_SIZE * 7),
		Position(CELL_SIZE * 9, CELL_SIZE * 15),
		Position(CELL_SIZE * 11, CELL_SIZE * 15)
		};

	sf::Texture m_Texture;
	sf::Sprite m_bodySprite;
	sf::Sprite m_faceSprite;

	unsigned char speed;
	Direction m_direction;
	Position m_pos;
	Position m_target;
	Position m_house;
	Position m_gate;
};

