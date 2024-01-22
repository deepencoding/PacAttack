#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Ghosts.hpp"

class GhostManager
{
public:
	GhostManager();
	void Draw(sf::RenderWindow&);
	void reset(std::array<Position, 4>);
	void Update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&, Paccy&);
private:
	std::array <Ghosts, 4> m_ghostArr;
};

