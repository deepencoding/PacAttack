#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "global.hpp"

void DrawText(const std::string&, sf::RenderWindow&, bool, float = 0, float = 0, unsigned int = CELL_SIZE);