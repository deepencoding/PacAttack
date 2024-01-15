#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/Paccy.hpp"
#include "../headers/Ghosts.hpp"

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

std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > convert_sketch(std::array<std::string, MAP_HEIGHT> i_Map, Paccy& pacman, Ghosts& ghost)
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

            case 'G':
                ghost.set_pos(CELL_SIZE * col, CELL_SIZE * row);
                break;

            case '0':
                // handle energizers
                OUT_MAP[col][row] = Cell::Empty;
                std::cout << "0";
                break;

            case 'o':
                // handle something
                OUT_MAP[col][row] = Cell::Empty;
                std::cout << "o";
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

int main()
{
    // ========================= Initialize game =========================
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCREEN_RESIZE_FACTOR, SCREEN_HEIGHT * SCREEN_RESIZE_FACTOR), "PacAttack - Pacman Clone", sf::Style::Close);
    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));
    unsigned lag = 0;
    std::chrono::time_point<std::chrono::steady_clock> prev_time;
    std::array<std::string, MAP_HEIGHT> mapSketch = {
        " ################### ",
        " #........#........# ",
        " #o##.###.#.###.##o# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.### # ###.#### ",
        "    #.#   0   #.#    ",
        "#####.# ##=## #.#####",
        "     .  # G #  .     ",
        "#####.# ##### #.#####",
        "    #.#       #.#    ",
        " ####.# ##### #.#### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #o.#.....P.....#.o# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### "
    };

    // ========================= Load assets =========================
    Paccy pacman;
    Ghosts red_ghost;

    std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > world = convert_sketch(mapSketch, pacman, red_ghost);


    prev_time = std::chrono::steady_clock::now();

    // ========================= Main game loop =========================
    while (window.isOpen())
    {
        unsigned dt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - prev_time).count();
        lag += dt;
        prev_time += std::chrono::microseconds(dt);
        sf::Event event;
        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;

            // ========================= Event loop =========================
            while (window.pollEvent(event))
            {
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
            pacman.update(world);
            red_ghost.update(world);

            if (FRAME_DURATION > lag)
            {
                window.clear();
                // ========================= Render or Draw =========================
                Draw_Map(world, window);
                pacman.Draw_Paccy(window);
                red_ghost.Draw_Ghost(window);

                window.display();
            }
        }

        
    }

    return 0;
}