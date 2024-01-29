#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "global.hpp"
#include "GhostManager.hpp"


class Paccy
{
public:
	Paccy();
	void Draw_Paccy(bool, sf::RenderWindow&, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&);
	void set_pos(short, short);
	Position get_pos() const;
	Direction get_dir() const;
	void update(unsigned char, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, GhostManager&, float);
	void set_dead(bool);
	bool get_dead() const;
	bool get_energy() const;
	void reset_pacman();
	unsigned short get_energizer_timer() const;
	bool get_animation_over() const;

private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	bool m_dead;

	Direction m_direction;
	Position m_pos;

	unsigned short energizer_timer;
	unsigned short animation_timer;
	bool m_animation_over;

	bool energized;
};

