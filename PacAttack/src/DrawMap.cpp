#include "../headers/DrawMap.hpp"

void Draw_Map(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, sf::RenderWindow& i_win)
{
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::CircleShape circle_shape;

    sf::Sprite map_sprite;
    sf::Texture map_texture;

    map_texture.loadFromFile("assets\\images\\Map16.png");

    map_sprite.setTexture(map_texture);

    for (unsigned row = 0; row < MAP_HEIGHT; row++)
    {
        for (unsigned col = 0; col < MAP_WIDTH; col++)
        {
            cell_shape.setPosition(sf::Vector2f(CELL_SIZE * col, CELL_SIZE * row));
            map_sprite.setPosition(sf::Vector2f(CELL_SIZE * col, CELL_SIZE * row));

            switch (i_map[col][row])
            {
            /*case Cell::Empty:
                cell_shape.setFillColor(sf::Color::Black);
                map_sprite.setTextureRect(sf::IntRect())

                i_win.draw(cell_shape);
                break;*/

            case Cell::Pellet:
                /*circle_shape.setRadius(CELL_SIZE / 8);
                circle_shape.setOrigin(CELL_SIZE / 8, CELL_SIZE / 8);
                circle_shape.setPosition(sf::Vector2f((CELL_SIZE * col) + (CELL_SIZE / 2), (CELL_SIZE * row) + (CELL_SIZE / 2)));*/

                map_sprite.setTextureRect(sf::IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));
                i_win.draw(map_sprite);
                break;

            case Cell::Door:
                //cell_shape.setFillColor(sf::Color::Magenta);

                map_sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
                i_win.draw(map_sprite);
                break;

            case Cell::Energizer:
                /*circle_shape.setRadius(CELL_SIZE / 4);
                circle_shape.setOrigin(CELL_SIZE / 4, CELL_SIZE / 4);
                circle_shape.setPosition(sf::Vector2f((CELL_SIZE * col) + (CELL_SIZE / 2), (CELL_SIZE * row) + (CELL_SIZE / 2)));*/

                map_sprite.setTextureRect(sf::IntRect(CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
                i_win.draw(map_sprite);
                break;

            case Cell::Wall:
            {
                cell_shape.setFillColor(sf::Color::Blue);

                bool down  = false;
                bool left  = false;
                bool right = false;
                bool up    = false;


                //I HAVE NO IDEA HOW THIS WORKS
                
                // Connect the tunnels
                if (col == MAP_WIDTH - 1) {
                    right = true;
                }
                else if (col == 0) {
                    left = true;
                }

                // everything else
                if (col != MAP_WIDTH - 1 && col != 0)
                {
                    if (i_map[static_cast<std::array<Cell, 21Ui64>::size_type>(col + 1)][row] == Cell::Wall)
                        right = true;
                    if (i_map[static_cast<std::array<Cell, 21Ui64>::size_type>(col - 1)][row] == Cell::Wall)
                        left = true;
                }
                else
                {
                    if (col == MAP_WIDTH - 1)
                    {
                        if (i_map[static_cast<std::array<Cell, 21Ui64>::size_type>(col - 1)][row] == Cell::Wall)
                            left = true;
                    }
                    else
                    {
                        if (i_map[static_cast<std::array<Cell, 21Ui64>::size_type>(col + 1)][row] == Cell::Wall)
                            right = true;
                    }
                }
                if (row <= MAP_HEIGHT - 1 && row >= 0) 
                {
                    if (row != MAP_HEIGHT - 1 && row != 0)
                    {
                        if (i_map[col][static_cast<std::array<std::array<Cell, 21Ui64>, 21Ui64>::size_type>(row + 1)] == Cell::Wall)
                            down = true;
                        if (i_map[col][static_cast<std::array<std::array<Cell, 21Ui64>, 21Ui64>::size_type>(row - 1)] == Cell::Wall)
                            up = true;
                    }
                    else
                    {
                        if (row == MAP_HEIGHT - 1)
                        {
                            if (i_map[col][static_cast<std::array<std::array<Cell, 21Ui64>, 21Ui64>::size_type>(row - 1)] == Cell::Wall)
                                up = true;
                        }
                        else
                        {
                            if (i_map[col][static_cast<std::array<std::array<Cell, 21Ui64>, 21Ui64>::size_type>(row + 1)] == Cell::Wall)
                                down = true;
                        }
                    }
                }

                //if (row < MAP_HEIGHT - 1)
                //{
                //    if (Cell::Wall == i_map[col][1 + row])
                //    {
                //        down = 1;
                //    }
                //}

                ////Since we have warp tunnels, we need to draw them as if they're connected.
                //if (0 < col)
                //{
                //    if (Cell::Wall == i_map[col - 1][row])
                //    {
                //        left = 1;
                //    }
                //}
                //else
                //{
                //    left = 1;
                //}

                //if (col < MAP_WIDTH - 1)
                //{
                //    if (Cell::Wall == i_map[1 + col][row])
                //    {
                //        right = 1;
                //    }
                //}
                //else
                //{
                //    right = 1;
                //}

                //if (0 < row)
                //{
                //    if (Cell::Wall == i_map[col][row - 1])
                //    {
                //        up = 1;
                //    }
                //}

                map_sprite.setTextureRect(sf::IntRect(CELL_SIZE * (up * 8 + right * 4 + left * 2 + down), 0, CELL_SIZE, CELL_SIZE));
                i_win.draw(map_sprite);
                break;
            }

            default:
                break;
            }
        }
    }
}