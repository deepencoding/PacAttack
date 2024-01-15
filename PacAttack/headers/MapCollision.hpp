#pragma once

#include <array>

#include "global.hpp"

bool map_collision(bool, short, short, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >&);