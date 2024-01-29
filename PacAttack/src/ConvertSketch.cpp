#include "../headers/ConvertSketch.hpp"

std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > convert_sketch(std::array<std::string, MAP_HEIGHT> i_Map, Paccy& pacman, std::array<Position, 4>& init_ghost_pos)
{
    std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > OUT_MAP{};
    for (unsigned row = 0; row < MAP_HEIGHT; row++)
    {
        for (unsigned col = 0; col < MAP_WIDTH; col++)
        {
            switch (i_Map[row][col])
            {
            case '#':
                OUT_MAP[col][row] = Cell::Wall;
                break;

            case ' ':
                OUT_MAP[col][row] = Cell::Empty;
                break;

            case 'P':
                pacman.set_pos(CELL_SIZE * col, CELL_SIZE * row);
                break;

            case 'r':
                init_ghost_pos[GHOST::BLINKY].x = CELL_SIZE * col;
                init_ghost_pos[GHOST::BLINKY].y = CELL_SIZE * row;
                break;

            case 'p':
                init_ghost_pos[GHOST::PINKY].x = CELL_SIZE * col;
                init_ghost_pos[GHOST::PINKY].y = CELL_SIZE * row;
                break;

            case 'b':
                init_ghost_pos[GHOST::INKY].x = CELL_SIZE * col;
                init_ghost_pos[GHOST::INKY].y = CELL_SIZE * row;
                break;

            case 'o':
                init_ghost_pos[GHOST::CLYDE].x = CELL_SIZE * col;
                init_ghost_pos[GHOST::CLYDE].y = CELL_SIZE * row;
                break;

            case 'e':
                // handle energizers
                OUT_MAP[col][row] = Cell::Energizer;
                break;

            case '.':
                // handle pellets
                OUT_MAP[col][row] = Cell::Pellet;
                break;

            case '=':
                OUT_MAP[col][row] = Cell::Door;
                break;

            default:
                break;
            }
        }
    }

    return OUT_MAP;
}