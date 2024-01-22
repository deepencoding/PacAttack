#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"
#include "../headers/Paccy.hpp"
#include "../headers/Ghosts.hpp"
#include "../headers/DrawMap.hpp"
#include "../headers/ConvertSketch.hpp"
#include "../headers/GhostManager.hpp"

int main()
{
    // ========================= Initialize game =========================
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCREEN_RESIZE_FACTOR, SCREEN_HEIGHT * SCREEN_RESIZE_FACTOR), "PacAttack - Pacman Clone", sf::Style::Close);

    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

    /*int HIGH_SCORE = 0;
    sf::Font font;
    font.loadFromFile("assets\\font\\Emulogic-zrEw.ttf");
    sf::Text highScore;
    highScore.setFont(font);
    highScore.setString(std::to_string(HIGH_SCORE));
    highScore.setCharacterSize(CELL_SIZE);
    highScore.setFillColor(sf::Color::White);
    highScore.setStyle(sf::Text::Bold);*/

    std::array<Position, 4> init_ghost_pos;

    unsigned lag = 0;
    std::chrono::time_point<std::chrono::steady_clock> prev_time;

    std::array<std::string, MAP_HEIGHT> mapSketch = {
        " ################### ",
        " #........#........# ",
        " #e##.###.#.###.##e# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.### # ###.#### ",
        "    #.#   r   #.#    ",
        "#####.# ##=## #.#####",
        "     .  #pbo#  .     ",
        "#####.# ##### #.#####",
        "    #.#       #.#    ",
        " ####.# ##### #.#### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #e.#.....P.....#.e# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### "
    };

    // ========================= Load assets =========================
    Paccy pacman;
    GhostManager manager;

    std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > world = convert_sketch(mapSketch, pacman, init_ghost_pos);

    manager.reset(init_ghost_pos);

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
            manager.Update(world, pacman);

            if (FRAME_DURATION > lag)
            {
                window.clear();
                // ========================= Render or Draw =========================
                Draw_Map(world, window);
                pacman.Draw_Paccy(window);
                manager.Draw(window);

                window.display();
            }
        }

        
    }

    return 0;
}