#include <iostream>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"

void Draw_Map(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, sf::RenderWindow& i_win)
{
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
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
                cell_shape.setFillColor(sf::Color::White);
                i_win.draw(cell_shape);
                break;

            default:
                break;
            }
        }
    }
}

std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > convert_sketch(std::array<std::string, MAP_HEIGHT> i_Map)
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

            default:
                break;
            }
        }
        std::cout << std::endl;
    }

    return OUT_MAP;
}

int main()
{
    // ========================= Initialize game =========================
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(672, 704), "PacAttack - Pacman Clone", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    std::array<std::string, MAP_HEIGHT> mapSketch = {
        " ################### ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        "                     ",
        "##                 ##",
        "                     ",
        "##                 ##",
        "                     ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " #                 # ",
        " ################### "
    };

    std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > world = convert_sketch(mapSketch);

    // ========================= Load assets =========================
    sf::Texture pacmanTexture;
    sf::Sprite pacmanSprite;
    if (pacmanTexture.loadFromFile("C:\\Dev\\Projects\\PacAttack\\PacAttack\\assets\\images\\Pacman16.png"))
    {
        std::cout << "Pacman texture loaded successfully" << std::endl;
        pacmanSprite.setTexture(pacmanTexture);
        int pacmanXIndex = 0;
        int pacmanYIndex = 0;
        int textureBit = 16;
        pacmanSprite.setTextureRect(sf::IntRect(pacmanXIndex * textureBit, pacmanYIndex * textureBit, textureBit, textureBit));
    }
    else
    {
		std::cout << "Error loading pacman texture" << std::endl;
	}

    // ========================= Main game loop =========================
    while (window.isOpen())
    {
        // ========================= Event loop =========================
        sf::Event event;
        while (window.pollEvent(event))
        {
            Draw_Map(world, window);
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        // ========================= Update game state =========================
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			pacmanSprite.move(-1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            pacmanSprite.move(1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pacmanSprite.move(0.f, -1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            pacmanSprite.move(0.f, 1.f);

        window.clear();
        // ========================= Render or Draw =========================
        window.draw(pacmanSprite);
        window.display();
    }

    return 0;
}