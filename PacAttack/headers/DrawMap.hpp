#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"

void Draw_Map(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, sf::RenderWindow& i_win);

