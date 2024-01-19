#include "../headers/ConvertSketch.hpp"

std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > convert_sketch(std::array<std::string, MAP_HEIGHT> i_Map, Paccy& pacman, Ghosts& red_ghost, Ghosts& orange_ghost, Ghosts& pink_ghost, Ghosts& blue_ghost)
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
                std::cout << "#";
                break;

            case ' ':
                OUT_MAP[col][row] = Cell::Empty;
                std::cout << " ";
                break;

            case 'P':
                pacman.set_pos(CELL_SIZE * col, CELL_SIZE * row);
                break;

            case 'r':
                red_ghost.set_pos(CELL_SIZE * col, CELL_SIZE * row);
                break;

            case 'p':
                pink_ghost.set_pos(CELL_SIZE * col, CELL_SIZE * row);
                break;

            case 'b':
                blue_ghost.set_pos(CELL_SIZE * col, CELL_SIZE * row);
                break;

            case 'o':
                orange_ghost.set_pos(CELL_SIZE * col, CELL_SIZE * row);
                break;

            case 'e':
                // handle something
                OUT_MAP[col][row] = Cell::Empty;
                std::cout << "e";
                break;

            case '.':
                // handle pellets
                OUT_MAP[col][row] = Cell::Pellet;
                std::cout << ".";
                break;

            default:
                break;
            }
        }
        std::cout << std::endl;
    }

    return OUT_MAP;
}