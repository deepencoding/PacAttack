#include <math.h>

#include "../headers/MapCollision.hpp"

bool map_collision(bool i_collect, short i_x, short i_y, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map)
{
	bool op = 0;

	float Cell_X = i_x / static_cast<float>(CELL_SIZE);
	float Cell_Y = i_y / static_cast<float>(CELL_SIZE);

	unsigned char Cell_Intersect = 4;

	for (unsigned char a = 0; a < Cell_Intersect; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
		case 0:
			x = static_cast<short>(floor(Cell_X));
			y = static_cast<short>(floor(Cell_Y));
			break;

		case 1:
			x = static_cast<short>(ceil(Cell_X));
			y = static_cast<short>(floor(Cell_Y));
			break;

		case 2:
			x = static_cast<short>(floor(Cell_X));
			y = static_cast<short>(ceil(Cell_Y));
			break;

		case 3:
			x = static_cast<short>(ceil(Cell_X));
			y = static_cast<short>(ceil(Cell_Y));
			break;

		default:
			break;
		}

		if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT)
		{
			if (i_collect == 1)
			{
				if (i_map[x][y] == Cell::Pellet)
				{
					i_map[x][y] = Cell::Empty;
				}
			}
			else
			{
				if (i_map[x][y] == Cell::Wall)
					op = 1;
			}
		}
	}
	return op;
}