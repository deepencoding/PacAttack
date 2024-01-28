#pragma once

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#include "Chronometer.hpp"
#include "Ghosts.hpp"

class GhostManager
{
public:
	GhostManager();
	void Draw(bool, sf::RenderWindow&);
	void reset(unsigned char, std::array<Position, 4>);
	void Update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, Paccy&, unsigned char);
	void switch_ghost_mode();
	MODE get_ghost_mode();
	void switch_frightened();
	sf::Time get_wave_timer() const;
	std::array<FRIGHT, 4> get_ghost_frightened() const;
	void pause_clock();
	void resume_clock();
private:
	std::array <Ghosts, 4> m_ghostArr;
	unsigned short curr_wave;
	sf::Time wave_timer;
	sftools::Chronometer ghost_clock;
	bool perma_chase;
	MODE ghost_mode;
};

