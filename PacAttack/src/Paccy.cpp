#include <iostream>

#include "../headers/Paccy.hpp"
#include "../headers/MapCollision.hpp"

Paccy::Paccy()
{
    m_direction = Direction::Right;
}

void Paccy::Draw_Paccy(sf::RenderWindow& window)
{
    m_Sprite.setPosition(m_pos.x, m_pos.y);
    if (m_Texture.loadFromFile("assets\\images\\Pacman16.png"))
    {
        m_Sprite.setTexture(m_Texture);
        m_Sprite.setTextureRect(sf::IntRect(m_XIndex * m_TextureBit, m_YIndex * m_TextureBit, m_TextureBit, m_TextureBit));
    }
    else
    {
        std::cout << "Error loading pacman texture" << std::endl;
    }
    window.draw(m_Sprite);
}

void Paccy::set_pos(short x, short y)
{
    m_pos = {
        x, y
    };
}

Position Paccy::get_pos() const
{
    return m_pos;
}

Direction Paccy::get_dir() const
{
    return m_direction;
}

void Paccy::update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, GhostManager& i_ghost_manager)
{
    std::array<bool, 4> walls {};

    walls[Direction::Right] = map_collision(0, 0, m_pos.x + PACMAN_SPEED, m_pos.y, i_map);
    walls[Direction::Up]    = map_collision(0, 0, m_pos.x, m_pos.y - PACMAN_SPEED, i_map);
    walls[Direction::Left]  = map_collision(0, 0, m_pos.x - PACMAN_SPEED, m_pos.y, i_map);
    walls[Direction::Down]  = map_collision(0, 0, m_pos.x, m_pos.y + PACMAN_SPEED, i_map);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (!walls[Direction::Right])
            m_direction = Direction::Right;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (!walls[Direction::Up])
            m_direction = Direction::Up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (!walls[Direction::Left])
            m_direction = Direction::Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (!walls[Direction::Down])
            m_direction = Direction::Down;
    }

    if (!walls[m_direction])
    {
        switch (m_direction)
        {
        case Direction::Right:
            m_pos.x += PACMAN_SPEED;
            break;

        case Direction::Up:
            m_pos.y -= PACMAN_SPEED;
            break;

        case Direction::Left:
            m_pos.x -= PACMAN_SPEED;
            break;

        case Direction::Down:
            m_pos.y += PACMAN_SPEED;
            break;

        default:
            break;
        }
    }

    if (m_pos.x <= -CELL_SIZE)
    {
        m_pos.x = CELL_SIZE * MAP_WIDTH;
    }
    else if (m_pos.x >= CELL_SIZE * MAP_WIDTH)
    {
        m_pos.x = -CELL_SIZE;
    }

    if (map_collision(0, 1, m_pos.x, m_pos.y, i_map))
    {
        energizer_timer = ENERGIZER_DURATION;
        i_ghost_manager.switch_frightened();
    }
    else
    {
        energizer_timer = std::max(energizer_timer - 1, 0);
        if (energizer_timer == 0)
        {
            i_ghost_manager.switch_frightened();
        }
    }
}

void Paccy::set_dead(bool i_dead)
{
    m_dead = i_dead;
    std::cout << "PACMAN DEAD" << std::endl;
}

bool Paccy::get_dead() const
{
    return m_dead;
}