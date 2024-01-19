#pragma once

#include <iostream>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "Paccy.hpp"
#include "Ghosts.hpp"

std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > convert_sketch(std::array<std::string, MAP_HEIGHT>, Paccy&, Ghosts&, Ghosts&, Ghosts&, Ghosts&);