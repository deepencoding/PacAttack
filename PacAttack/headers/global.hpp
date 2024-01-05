#pragma once

constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char FONT_HEIGHT = 16;
constexpr unsigned char MAP_WIDTH = 21;
constexpr unsigned char MAP_HEIGHT = 21;

constexpr unsigned char SCREEN_RESIZE_FACTOR = 2;

constexpr unsigned char SCREEN_WIDTH = MAP_WIDTH * CELL_SIZE * SCREEN_RESIZE_FACTOR;
constexpr unsigned char SCREEN_HEIGHT = (FONT_HEIGHT + (MAP_HEIGHT * CELL_SIZE)) * SCREEN_RESIZE_FACTOR;

constexpr unsigned short FRAME_DURATION = 16667;