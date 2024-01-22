#include "../headers/GhostManager.hpp"
#include "../headers/global.hpp"
#include "../headers/Ghosts.hpp"

GhostManager::GhostManager()
	: m_ghostArr({
    Ghosts (GHOST::BLINKY),
    Ghosts (GHOST::CLYDE),
    Ghosts (GHOST::PINKY),
    Ghosts (GHOST::INKY) })
{
}

void GhostManager::Draw(sf::RenderWindow& i_win)
{
    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.Draw_Ghost(i_win);
    }
}

void GhostManager::reset(std::array<Position, 4> init_ghost_pos)
{
    for (unsigned iter = 0; iter < 4; iter++)
    {
        m_ghostArr[iter].set_pos(init_ghost_pos[iter].x, init_ghost_pos[iter].y);
    }

    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.reset_ghost(m_ghostArr[static_cast<unsigned>(GHOST::INKY)].get_pos(), m_ghostArr[static_cast<unsigned>(GHOST::BLINKY)].get_pos());
    }
}

void GhostManager::Update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, Paccy& i_pacman)
{
    for (Ghosts& ghost : m_ghostArr)
    {
        ghost.update(i_map, i_pacman, m_ghostArr[static_cast<unsigned>(GHOST::BLINKY)]);
    }
}
