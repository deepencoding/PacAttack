#pragma once

// blocks
static constexpr unsigned char CELL_SIZE = 16;
static constexpr unsigned char FONT_HEIGHT = 16;
static constexpr unsigned char MAP_WIDTH = 21;
static constexpr unsigned char MAP_HEIGHT = 21;

static constexpr unsigned char TEXTURE_BIT = 16;

static constexpr unsigned char SCREEN_RESIZE_FACTOR = 2;

static constexpr unsigned short SCREEN_WIDTH = MAP_WIDTH * CELL_SIZE;
static constexpr unsigned short SCREEN_HEIGHT = (FONT_HEIGHT + (MAP_HEIGHT * CELL_SIZE));

// speed factor
static constexpr unsigned char PACMAN_SPEED = 2;
static constexpr unsigned char GHOST_SPEED = 1;
static constexpr unsigned char GHOST_ESCAPE_SPEED = 4;

// v This is the amount of times ghosts wait before moving each frame v
static constexpr unsigned char GHOST_FRIGHTENED_SPEED = 3;
static constexpr unsigned char GHOST_TUNNEL_SPEED = 3;

static constexpr unsigned char PACMAN_ANIMATION_SPEED = 3;

static constexpr unsigned char GHOST_ANIMATION_SPEED = 3;
static constexpr unsigned char GHOST_FLASH_TIME = 80;

// number of blocks
static constexpr unsigned char CLYDE_DIST = 4;
static constexpr unsigned char PINKY_DIST = 4;
static constexpr unsigned char INKY_DIST = 2;

// frames
static constexpr unsigned short GHOST_ANIMATION_FRAMES = 6;
static constexpr unsigned short PACMAN_ANIMATION_FRAMES = 6;
static constexpr unsigned short PACMAN_DEATH_FRAMES = 12;

static constexpr unsigned short FRAME_DURATION = 16667;
static constexpr unsigned short LONG_SCATTER_DURATION = 512;
static constexpr unsigned short SHORT_SCATTER_DURATION = 256;
static constexpr unsigned short ENERGIZER_DURATION = 512;
static constexpr unsigned short GHOST_FRIGHTENED_WAIT = 512;


enum Direction {
	Right = 0, Up, Left, Down, Undef
};

static Direction get_opposite_dir(Direction dir)
{
	return static_cast<Direction>((dir + 2) % 4);
}

enum class Cell {
	Empty, Wall, Pellet, Door, Energizer
};

enum GHOST {
	BLINKY = 0, CLYDE, PINKY, INKY
};

enum MODE {
	SCATTER = 0, CHASE
};

enum FRIGHT {
	NONE = 0, LITTLE, FULLY
};

struct Position
{
	short x = 0;
	short y = 0;

	Position () {}

	Position (short _x, short _y)
		: x(_x), y(_y)
	{}

	bool operator == (Position& p)
	{
		return (this->x == p.x && this->y == p.y);
	}
};