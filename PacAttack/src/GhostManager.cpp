#include "../headers/GhostManager.hpp"
#include "../headers/global.hpp"

GhostManager::GhostManager()
	: curr_wave(1), wave_timer(sf::seconds(7.f)), perma_chase(false), ghost_clock(wave_timer),
    m_ghostArr({
    Ghosts (GHOST::BLINKY),
    Ghosts (GHOST::CLYDE),
    Ghosts (GHOST::PINKY),
    Ghosts (GHOST::INKY) }) 
{
    ghost_clock.resume();
}

void GhostManager::Draw(bool i_flash, sf::RenderWindow& i_win)
{
    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.Draw_Ghost(i_flash, i_win);
    }
}

void GhostManager::reset(unsigned char curr_lvl, std::array<Position, 4> init_ghost_pos)
{
    perma_chase = false;

    curr_wave = 1;

    //wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION/pow(2, curr_lvl));
    ghost_clock.reset(true);
    if (curr_lvl == 1)
        wave_timer = sf::seconds(7.f);
    else if (curr_lvl >= 5)
        wave_timer = sf::seconds(5.f);

    for (unsigned iter = 0; iter < 4; iter++)
    {
        m_ghostArr[iter].set_pos(init_ghost_pos[iter].x, init_ghost_pos[iter].y);
    }

    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.reset_ghost(m_ghostArr[static_cast<unsigned>(GHOST::INKY)].get_pos(), m_ghostArr[static_cast<unsigned>(GHOST::BLINKY)].get_pos());
    }
}

void GhostManager::Update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, Paccy& i_pacman, unsigned char curr_lvl, bool i_gameNotStarted)
{
    // std::cout << (unsigned)wave_timer.asSeconds() << std::endl;
    // std::cout << (unsigned)ghost_clock.getElapsedTime().asSeconds() << std::endl;
    // std::cout << ghost_mode << std::endl;
    ghost_mode = get_ghost_mode();
    if (i_gameNotStarted == false)
    {
        if (curr_lvl == 1)
        {
            if (curr_wave == 1)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    if (ghost_mode == MODE::SCATTER)
                    {
                        wave_timer = sf::seconds(20.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                    else
                    {
                        curr_wave++;
                        wave_timer = sf::seconds(7.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                }
            }
            else if (curr_wave == 2 || curr_wave == 3)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    if (ghost_mode == MODE::SCATTER)
                    {
                        wave_timer = sf::seconds(20.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();

                    }
                    else
                    {
                        curr_wave++;
                        wave_timer = sf::seconds(5.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                }
            }
            else if (curr_wave == 4)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    perma_chase = true;
                    switch_ghost_mode();
                }
            }
        }
        else if (curr_lvl == 2)
        {
            if (curr_wave == 1)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    if (ghost_mode == MODE::SCATTER)
                    {
                        wave_timer = sf::seconds(20.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                    else
                    {
                        curr_wave++;
                        wave_timer = sf::seconds(7.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                }
            }
            else if (curr_wave == 2 || curr_wave == 3)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    if (ghost_mode == MODE::SCATTER)
                    {
                        wave_timer = sf::seconds(20.f);
                        ghost_clock.reset(true);
                        if (curr_wave == 3)
                            wave_timer = sf::seconds(1033.f);
                        switch_ghost_mode();
                    }
                    else
                    {
                        curr_wave++;
                        wave_timer = sf::milliseconds(16.67f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                }
            }
            else if (curr_wave == 4)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    perma_chase = true;
                    switch_ghost_mode();
                }
            }
        }
        else if (curr_lvl >= 5)
        {
            if (curr_wave == 1)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    if (ghost_mode == MODE::SCATTER)
                    {
                        wave_timer = sf::seconds(20.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                    else
                    {
                        curr_wave++;
                        wave_timer = sf::seconds(7.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                }
            }
            else if (curr_wave == 2 || curr_wave == 3)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    if (ghost_mode == MODE::SCATTER)
                    {
                        wave_timer = sf::seconds(20.f);
                        if (curr_wave == 3)
                            wave_timer = sf::seconds(1037.f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                    else
                    {
                        curr_wave++;
                        wave_timer = sf::milliseconds(16.67f);
                        ghost_clock.reset(true);
                        switch_ghost_mode();
                    }
                }
            }
            else if (curr_wave == 4)
            {
                if ((unsigned)ghost_clock.getElapsedTime().asSeconds() == (unsigned)wave_timer.asSeconds() && perma_chase == false)
                {
                    perma_chase = true;
                    switch_ghost_mode();
                }
            }
        }
    }
    else
    {
        ghost_clock.reset();
    }

    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.update(curr_lvl, i_map, i_pacman, m_ghostArr[static_cast<unsigned>(GHOST::BLINKY)]);
    }
}

void GhostManager::switch_ghost_mode()
{
    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.switch_mode();
    }
}

MODE GhostManager::get_ghost_mode()
{
    return m_ghostArr[0].get_mode();
}

void GhostManager::switch_frightened()
{
    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.switch_frightened();
    }
}

sf::Time GhostManager::get_wave_timer() const
{
    return wave_timer;
}

std::array<FRIGHT, 4> GhostManager::get_ghost_frightened() const
{
    std::array<FRIGHT, 4> op{};
    for (unsigned iter = 0; iter < 4; iter++)
    {
        op[iter] = m_ghostArr[iter].get_frightened();
    }
    return op;
}

void GhostManager::pause_clock()
{
    ghost_clock.pause();
}

void GhostManager::resume_clock()
{
    ghost_clock.resume();
}

void GhostManager::reset_clock()
{
    ghost_clock.reset();
}
