#pragma once

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#include "Ghosts.hpp"

class GhostManager
{
public:
	GhostManager();
	void Draw(sf::RenderWindow&);
	void reset(unsigned char, std::array<Position, 4>);
	void Update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, Paccy&, unsigned char);
	void switch_ghost_mode();
	MODE get_ghost_mode();
	void switch_frightened();
private:
	std::array <Ghosts, 4> m_ghostArr;
	unsigned short curr_wave;
	sf::Clock ghost_clock;
	sf::Time wave_timer;
	bool perma_chase;
	MODE ghost_mode;
};

