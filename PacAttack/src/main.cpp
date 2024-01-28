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
#include "../headers/DrawText.hpp"

int main()
{
    // ========================= Initialize game =========================
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCREEN_RESIZE_FACTOR, (SCREEN_HEIGHT + CELL_SIZE) * SCREEN_RESIZE_FACTOR), "PacAttack - Pacman Clone", sf::Style::Close);

    window.setView(sf::View(sf::FloatRect(0, -CELL_SIZE, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + (CELL_SIZE + 1) * MAP_HEIGHT)));

    /*sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCREEN_RESIZE_FACTOR, SCREEN_HEIGHT * SCREEN_RESIZE_FACTOR), "PacAttack - Pacman Clone", sf::Style::Close);

    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));*/

    bool game_won = false;
    bool gameNotStarted = true;
    unsigned char level = 1;
    long curr_score = -4400; // -4400 because it counts already empty cells

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
    GhostManager manager;
    Paccy pacman;
    manager.pause_clock();

    std::array<std::array<bool, MAP_WIDTH>, MAP_HEIGHT> added_map{};
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> world = convert_sketch(mapSketch, pacman, init_ghost_pos);
    std::array<bool, 4> added_ghost{};

    manager.reset(level, init_ghost_pos);

    prev_time = std::chrono::steady_clock::now();

    // ========================= Main game loop =========================
    while (window.isOpen())
    {
        unsigned dt = (unsigned) std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - prev_time).count();
        lag += dt;
        prev_time += std::chrono::microseconds(dt);
        if (gameNotStarted)
        {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && gameNotStarted) {
                gameNotStarted = false;
                manager.resume_clock();
            }
        }

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
            if (!pacman.get_dead() && game_won == false && gameNotStarted == false)
            {
                game_won = true;
                
                manager.Update(world, pacman, level);
                pacman.update(level, world, manager, fps);
                
                // short cnt = 0;
                // curr_score -= 4400;
                for (unsigned row = 0; row < MAP_HEIGHT; row++)
                {
                    for (unsigned col = 0; col < MAP_WIDTH; col++)
                    {
                        if (world[row][col] == Cell::Pellet) // if there are still pellets left, game is not won
                        {
                            game_won = false;
                        }
                        else if (world[row][col] == Cell::Empty && added_map[row][col] == false)
                        {
                            curr_score +=  50;
                            added_map[row][col] = true;
                        }
                    }
                }
                std::array<FRIGHT, 4> fright = manager.get_ghost_frightened();
                if (pacman.get_energy())
                {
                    for (unsigned iter = 0; iter < 4; iter++)
                    {
                        if (fright[iter] == FRIGHT::FULLY && added_ghost[iter] == false)
                        {
                            curr_score += 500;
                            added_ghost[iter] = true;
                        }
                    }
                }
                else
                {
                    for (unsigned i = 0; i < 4; i++)
                    {
                        added_ghost[i] = false;
                    }
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                game_won = 0;
                if (pacman.get_dead())
                {
                    gameNotStarted = false;
                    level = 1;
                    curr_score = -4400;
                }
                else {
                    gameNotStarted = false;
                    level++;
                }
                world = convert_sketch(mapSketch, pacman, init_ghost_pos);
                manager.reset(level, init_ghost_pos);
                pacman.reset_pacman();
                for (unsigned row = 0; row < MAP_HEIGHT; row++)
                {
                    for (unsigned col = 0; col < MAP_WIDTH; col++)
                    {
                        added_map[row][col] = false;
                        
                    }
                }
            }

            if (FRAME_DURATION > lag)
            {
                start = std::chrono::high_resolution_clock::now();
                window.clear();
                // ========================= Render or Draw =========================
                if (!pacman.get_dead() && game_won == false)
                {
                    Draw_Map(world, window);
                    manager.Draw(pacman.get_energizer_timer() <= GHOST_FLASH_TIME, window);
                }
                pacman.Draw_Paccy(game_won, window, world);
                DrawText("Level: " + std::to_string(level), window, false, 0, MAP_HEIGHT);
                if (gameNotStarted == false)
                {
                    DrawText("Score: " + std::to_string(curr_score), window, false, 0.f, -0.6f, CELL_SIZE / 2);
                }

                if (pacman.get_animation_over())
                {
                    if (game_won)
                    {
                        DrawText("GameWon", window, true);
                    }
                    else
                    {
                        DrawText("GameOver", window, true);
                    }
                }

                if (gameNotStarted)
                {
                    DrawText("Enter or Space", window, true, true);
                }

                window.display();
                end = std::chrono::high_resolution_clock::now();
                fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }        
    }

    return 0;
}