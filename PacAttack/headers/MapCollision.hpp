#pragma once

#include <array>

#include "global.hpp"
#include "Paccy.hpp"

bool map_collision(bool, bool, short, short, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&);