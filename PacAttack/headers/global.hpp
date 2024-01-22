#pragma once

static constexpr unsigned char CELL_SIZE = 16;
static constexpr unsigned char FONT_HEIGHT = 16;
static constexpr unsigned char MAP_WIDTH = 21;
static constexpr unsigned char MAP_HEIGHT = 21;

static constexpr unsigned char SCREEN_RESIZE_FACTOR = 2;

static constexpr unsigned short SCREEN_WIDTH = MAP_WIDTH * CELL_SIZE;
static constexpr unsigned short SCREEN_HEIGHT = (FONT_HEIGHT + (MAP_HEIGHT * CELL_SIZE));

static constexpr unsigned short FRAME_DURATION = 16667;

static constexpr unsigned char PACMAN_SPEED = 2;
static constexpr unsigned char GHOST_SPEED = 2;

static constexpr unsigned char CLYDE_DIST = 4;
static constexpr unsigned char PINKY_DIST = 4;
static constexpr unsigned char INKY_DIST = 2;

enum Direction {
	Right = 0, Up, Left, Down, Undef
};

static Direction get_opposite_dir(Direction dir)
{
	return static_cast<Direction>((dir + 2) % 4);
}

enum class Cell {
	Empty, Wall, Pellet
};

enum GHOST {
	BLINKY = 0, CLYDE, PINKY, INKY
};

enum MODE {
	SCATTER = 0, CHASE
};

struct Position
{
	short x;
	short y;

	Position () {}

	Position (short _x, short _y)
		: x(_x), y(_y)
	{}

	bool operator == (Position& p)
	{
		return (this->x == p.x && this->y == p.y);
	}
};