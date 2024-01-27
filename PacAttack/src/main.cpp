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

    bool game_won = false;
    unsigned char level = 1;

    std::array<Position, 4> init_ghost_pos;

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    float fps = 240.f;

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

    manager.reset(level, init_ghost_pos);

    prev_time = std::chrono::steady_clock::now();

    // ========================= Main game loop =========================
    while (window.isOpen())
    {
        unsigned dt = (unsigned) std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - prev_time).count();
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
            if (!pacman.get_dead() && game_won == false)
            {
                game_won = true;
                pacman.update(level, world, manager, fps);
                manager.Update(world, pacman, level);
                for (std::array < Cell, MAP_WIDTH >& row : world)
                {
                    for (Cell& cell : row)
                    {
                        if (cell == Cell::Pellet) // if there are still pellets left, game is not won
                        {
                            game_won = false;
                            break;
                        }
                    }
                    if (game_won == false) {
                        break;
                    }
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                game_won = 0;
                if (pacman.get_dead())
                {
                    level = 1;
                }
                else {
                    level++;
                }
                world = convert_sketch(mapSketch, pacman, init_ghost_pos);
                manager.reset(level, init_ghost_pos);
                pacman.reset_pacman();

            }

            if (FRAME_DURATION > lag)
            {
                start = std::chrono::high_resolution_clock::now();
                window.clear();
                // ========================= Render or Draw =========================
                if (!pacman.get_dead() && game_won == false)
                {
                    Draw_Map(world, window);
                    manager.Draw(window);
                }
                pacman.Draw_Paccy(game_won, window);

                window.display();
                end = std::chrono::high_resolution_clock::now();
                fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }        
    }

    return 0;
}