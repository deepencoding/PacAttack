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

    sf::Image icon;
    icon.loadFromFile("assets\\icon\\Pacman_1.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


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
    
    unsigned char alt_munch = 0;
    bool munch_not_playing = true;
    sf::Sound munch_1;
    sf::SoundBuffer munch_1_buffer;
    munch_1_buffer.loadFromFile("assets\\sound\\Pac-Man\\munch_1.wav");
    munch_1.setBuffer(munch_1_buffer);
    munch_1.setVolume(30);
    
    sf::Sound munch_2;
    sf::SoundBuffer munch_2_buffer;
    munch_2_buffer.loadFromFile("assets\\sound\\Pac-Man\\munch_2.wav");
    munch_2.setBuffer(munch_2_buffer);
    munch_2.setVolume(30);

    bool not_played_death = true;
    sf::Sound death;
    sf::SoundBuffer death_buffer;
    death_buffer.loadFromFile("assets\\sound\\pacman-death\\pacman_death.wav");
    death.setBuffer(death_buffer);
    death.setLoop(false);

    bool energized_not_playing = true;
    sf::Sound energized_pacman;
    sf::SoundBuffer energized_pacman_buffer;
    energized_pacman_buffer.loadFromFile("assets\\sound\\Pac-Man\\power_pellet.wav");
    energized_pacman.setBuffer(energized_pacman_buffer);
    energized_pacman.setLoop(true);

    bool hasNotPlayedLevelWon = true;
    sf::Sound level_won;
    sf::SoundBuffer level_won_buffer;
    level_won_buffer.loadFromFile("assets\\sound\\Pac-Man\\extend.wav");
    level_won.setBuffer(level_won_buffer);

    
    sf::Sound retreating;
    sf::SoundBuffer retreating_buffer;
    retreating_buffer.loadFromFile("assets\\sound\\Pac-Man\\retreating.wav");
    retreating.setBuffer(retreating_buffer);
    retreating.setLoop(true);
    

    std::array<sf::SoundBuffer, 5> siren_sound_buffers{};
    for (unsigned i = 0; i < 5; i++)
    {
        siren_sound_buffers[i].loadFromFile("assets\\sound\\Pac-Man\\siren_" + std::to_string(i+1) + ".wav");
    }

    std::array<sf::Sound, 5> siren_sounds{};
    for (unsigned i = 0; i < 5; i++)
    {
        siren_sounds[i].setBuffer(siren_sound_buffers[i]);
        siren_sounds[i].setLoop(true);
    }

    sf::Sprite pacman_ph;
    sf::Texture pacman_tx;
    pacman_tx.loadFromFile("assets\\images\\Pacman16.png");
    pacman_ph.setTexture(pacman_tx);
    pacman_ph.setTextureRect(sf::IntRect(3 * TEXTURE_BIT, 0, TEXTURE_BIT, TEXTURE_BIT));


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
                
                manager.Update(world, pacman, level, gameNotStarted);
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
                // std::cout << "new: " << new_pellets << "prev: " << pellets << std::endl;
                if (new_pellets < pellets)
                {
                    // chomp.setPlayingOffset(chomp.getPlayingOffset());
                    /*if (chomp.getStatus() != sf::SoundSource::Status::Playing && energized_not_playing)
                    {
                        death.stop();
                        not_played_death = true;
                        chomp.play();
                    }*/

                    //std::cout << "eating " << std::endl;

                    if (alt_munch == 0 && munch_1.getStatus() != sf::SoundSource::Status::Playing && munch_2.getStatus() != sf::SoundSource::Status::Playing && energized_not_playing)
                    {
                        death.stop();
                        not_played_death = true;
                        munch_1.play();
                        alt_munch = (alt_munch + 1) % 2;
                        munch_not_playing = false;
                    }
                    else if (alt_munch == 1 && munch_1.getStatus() != sf::SoundSource::Status::Playing && munch_2.getStatus() != sf::SoundSource::Status::Playing && energized_not_playing)
                    {
                        death.stop();
                        not_played_death = true;
                        munch_2.play();
                        alt_munch = (alt_munch + 1) % 2;
                        munch_not_playing = false;
                    }
                    pellets = new_pellets;
                }

                if (pacman.get_energizer_timer() != 0)
                {
                    if (energized_pacman.getStatus() != sf::SoundSource::Status::Playing)
                    {
                        munch_1.stop();
                        munch_2.stop();
                        if (level <= 5)
                        {
                            siren_sounds[level - 1].stop();
                        }
                        else
                        {
                            siren_sounds[4].stop();
                        }
                        energized_not_playing = false;
                        energized_pacman.play();
                    }
                }
                else
                {
                    energized_not_playing = true;
                    energized_pacman.stop();
                    if (new_pellets < pellets)
                    {
                        // std::cout << "eating " << std::endl;

                        if (alt_munch == 0 && munch_1.getStatus() != sf::SoundSource::Status::Playing && munch_2.getStatus() != sf::SoundSource::Status::Playing && energized_not_playing)
                        {
                            death.stop();
                            not_played_death = true;
                            munch_1.play();
                            alt_munch = (alt_munch + 1) % 2;
                            munch_not_playing = false;
                        }
                        else if (alt_munch == 1 && munch_1.getStatus() != sf::SoundSource::Status::Playing && munch_2.getStatus() != sf::SoundSource::Status::Playing && energized_not_playing)
                        {
                            death.stop();
                            not_played_death = true;
                            munch_2.play();
                            alt_munch = (alt_munch + 1) % 2;
                            munch_not_playing = false;
                        }
                        pellets = new_pellets;
                    }

                }
                std::array<FRIGHT, 4> fright = manager.get_ghost_frightened();
                if (pacman.get_energy())
                {
                    for (unsigned iter = 0; iter < 4; iter++)
                    {
                        if (fright[iter] == FRIGHT::FULLY) 
                        {
                            if (retreating.getStatus() != sf::Sound::Playing)
                            {
                                retreating.play();
                            }
                            if (added_ghost[iter] == false)
                            {
                                curr_score += 500;
                                high_score = std::max(curr_score, high_score);
                                added_ghost[iter] = true;
                            }
                        }
                        else if (fright[iter] == FRIGHT::NONE)
                        {
                            retreating.stop();
                        }
                    }
                }
                else
                {
                    retreating.stop();
                    for (unsigned i = 0; i < 4; i++)
                    {
                        added_ghost[i] = false;
                    }
                    if (level <= 5) 
                    {
                        //std::cout << level << std::endl;
                        if (siren_sounds[level - 1].getStatus() != sf::Sound::Playing)
                        {
                            // std::cout << 2 << std::endl;
                            siren_sounds[level - 1].play();
                        }
                    }
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                hasNotPlayedLevelWon = true;
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
                if (level <= 5)
                {
                    // std::cout << level << std::endl;
                    if (siren_sounds[level - 1].getStatus() != sf::Sound::Playing)
                    {
                        // std::cout << 3 << std::endl;
                        siren_sounds[level - 1].play();
                    }
                }
                else {
                    if (siren_sounds[4].getStatus() != sf::SoundSource::Playing)
                    {
                        siren_sounds[4].play();
                    }
                }
                world = convert_sketch(mapSketch, pacman, init_ghost_pos);
                manager.reset(level, init_ghost_pos);
                pacman.reset_pacman();
                munch_1.stop();
                munch_2.stop();
                for (unsigned row = 0; row < MAP_HEIGHT; row++)
                {
                    for (unsigned col = 0; col < MAP_WIDTH; col++)
                    {
                        added_map[row][col] = false;
                        
                    }
                }
            }
            else
            {
                manager.reset_clock();
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

                

                if (pacman.get_dead())
                {
                    if (death.getStatus() != sf::SoundSource::Status::Playing && not_played_death)
                    {
                        death.play();
                        not_played_death = false;
                    }
                }

                if (pacman.get_animation_over())
                {
                    if (game_won)
                    {
                        DrawText("GameWon", window, true);
                        munch_1.stop();
                        munch_2.stop();
                        energized_pacman.stop();
                        if (level <= 5)
                        {
                            siren_sounds[level - 1].stop();
                        }
                        else {
                            siren_sounds[4].stop();
                        }
                        if (level_won.getStatus() != sf::Sound::Playing && hasNotPlayedLevelWon)
                        {
                            level_won.play();
                            hasNotPlayedLevelWon = false;
                        }
                        
                    }
                    else
                    {
                        DrawText("GameOver", window, true);
                        munch_1.stop();
                        munch_2.stop();
                        energized_pacman.stop();
                        if (level <= 5)
                        {
                            siren_sounds[level - 1].stop();                            
                        }
                        else {
                            siren_sounds[4].stop();
                        }
                    }
                }

                if (gameNotStarted)
                {
                    pacman_ph.setPosition(sf::Vector2f(4.f * CELL_SIZE, -0.8f * CELL_SIZE));
                    pacman_ph.setScale(sf::Vector2f(0.8f, 0.8f));
                    window.draw(pacman_ph);
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