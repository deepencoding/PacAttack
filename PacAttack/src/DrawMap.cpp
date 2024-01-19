#include "../headers/DrawMap.hpp"

void Draw_Map(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, sf::RenderWindow& i_win)
{
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::CircleShape circle_shape;
    for (unsigned row = 0; row < MAP_HEIGHT; row++)
    {
        for (unsigned col = 0; col < MAP_WIDTH; col++)
        {
            cell_shape.setPosition(sf::Vector2f(CELL_SIZE * col, CELL_SIZE * row));

            switch (i_map[col][row])
            {
            case Cell::Wall:
                cell_shape.setFillColor(sf::Color::Blue);
                i_win.draw(cell_shape);
                break;

            case Cell::Empty:
                cell_shape.setFillColor(sf::Color::Black);
                i_win.draw(cell_shape);
                break;

            case Cell::Pellet:
                circle_shape.setRadius(CELL_SIZE / 8);
                circle_shape.setOrigin(CELL_SIZE / 8, CELL_SIZE / 8);
                circle_shape.setPosition(sf::Vector2f((CELL_SIZE * col) + (CELL_SIZE / 2), (CELL_SIZE * row) + (CELL_SIZE / 2)));
                i_win.draw(circle_shape);
                break;

            default:
                break;
            }
        }
    }
}