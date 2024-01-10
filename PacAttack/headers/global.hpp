#pragma once

constexpr unsigned int CELL_SIZE = 16;
constexpr unsigned int FONT_HEIGHT = 16;
constexpr unsigned int MAP_WIDTH = 21;
constexpr unsigned int MAP_HEIGHT = 21;

constexpr unsigned char SCREEN_RESIZE_FACTOR = 2;

int SCREEN_WIDTH = 21 * 16 * 2;
int SCREEN_HEIGHT = (16 + (21 * 16)) * 2;

constexpr unsigned short FRAME_DURATION = 16667;

//enum class Cell {
//	Door = 0, Empty, Energizer, Pellet, Wall
//};
enum class Cell {
	Empty, Wall
};