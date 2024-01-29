#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
    long high_score = curr_score;

    std::array<Position, 4> init_ghost_pos;

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    float fps = 240.f;

    unsigned lag = 0;
    std::chrono::time_point<std::chrono::steady_clock> prev_time;

    short pellets = 146 + 83;
    short energizers = 4;

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

    sf::Sound menu_music;
    sf::SoundBuffer menu_sound_buffer;
    menu_sound_buffer.loadFromFile("assets\\sound\\pacman-beginning\\pacman_beginning.wav");
    menu_music.setVolume(30);

    menu_music.setBuffer(menu_sound_buffer);
    menu_music.setLoop(true);
    menu_music.play();

    sf::Sound chomp;
    sf::SoundBuffer chomp_buffer;
    chomp_buffer.loadFromFile("assets\\sound\\pacman-chomp\\pacman_chomp.wav");
    chomp.setBuffer(chomp_buffer);
    chomp.setLoop(true);
    chomp.setVolume(30);

    sf::Sound death;
    sf::SoundBuffer death_buffer;
    death_buffer.loadFromFile("assets\\sound\\pacman-death\\pacman_death.wav");
    death.setBuffer(death_buffer);

    sf::Sound eatghost;
    sf::SoundBuffer eatghost_buffer;
    eatghost_buffer.loadFromFile("assets\\sound\\pacman-eatghost\\pacman_eatghost.wav");
    eatghost.setBuffer(eatghost_buffer);



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
                short new_pellets = pellets; // init empty cells
                short new_energizers = energizers;
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
                            new_pellets -= 1;
                            curr_score +=  50;
                            high_score = std::max(curr_score, high_score);
                            added_map[row][col] = true;
                        }
                    }
                }
                if (new_pellets < pellets)
                {
                    // chomp.setPlayingOffset(chomp.getPlayingOffset());
                    if (chomp.getStatus() != sf::SoundSource::Status::Playing)
                    {
                        chomp.play();
                    }
                    pellets = new_pellets;
                }
                std::array<FRIGHT, 4> fright = manager.get_ghost_frightened();
                if (pacman.get_energy())
                {
                    for (unsigned iter = 0; iter < 4; iter++)
                    {
                        if (fright[iter] == FRIGHT::FULLY && added_ghost[iter] == false)
                        {
                            curr_score += 500;
                            high_score = std::max(curr_score, high_score);
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
                chomp.stop();
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
                    DrawText("HighScore: " + std::to_string(high_score), window, false, 10.f, -0.6f, CELL_SIZE / 2);
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
                    DrawText("PacAttack", window, false, 5.f, -0.6f, CELL_SIZE / 2);
                    DrawText("-by deepencoding", window, false, 10.5f, -0.3f, CELL_SIZE / 3);
                    DrawText("Enter or Space", window, true, true);
                }

                if (gameNotStarted == false)
                {
                    menu_music.stop();
                }

                window.display();
                end = std::chrono::high_resolution_clock::now();
                fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }        
    }

    return 0;
}