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
    Ghosts red_ghost(GHOST::BLINKY);
    Ghosts orange_ghost(GHOST::CLYDE);
    Ghosts pink_ghost(GHOST::PINKY);
    Ghosts blue_ghost(GHOST::INKY);

    std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT > world = convert_sketch(mapSketch, pacman, red_ghost, orange_ghost, pink_ghost, blue_ghost);


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
            red_ghost.update(world, pacman, red_ghost);
            orange_ghost.update(world, pacman, red_ghost);
            pink_ghost.update(world, pacman, red_ghost);
            blue_ghost.update(world, pacman, red_ghost);

            if (FRAME_DURATION > lag)
            {
                window.clear();
                // ========================= Render or Draw =========================
                Draw_Map(world, window);
                pacman.Draw_Paccy(window);
                red_ghost.Draw_Ghost(window);
                orange_ghost.Draw_Ghost(window);
                pink_ghost.Draw_Ghost(window);
                blue_ghost.Draw_Ghost(window);

                window.display();
            }
        }

        
    }

    return 0;
}