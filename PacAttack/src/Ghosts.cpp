#include <iostream>

#include "../headers/MapCollision.hpp"
#include "../headers/Ghosts.hpp"

void Ghosts::Draw_Ghost(sf::RenderWindow& window)
{
    m_Sprite.setPosition(m_pos.x, m_pos.y);
    if (m_Texture.loadFromFile("assets\\images\\Ghost16.png"))
    {
        std::cout << "Ghost texture loaded successfully" << std::endl;
        m_Sprite.setTexture(m_Texture);
        m_Sprite.setTextureRect(sf::IntRect(m_XIndex * m_TextureBit, m_YIndex * m_TextureBit, m_TextureBit, m_TextureBit));
    }
    else
    {
        std::cout << "Error loading pacman texture" << std::endl;
    }
    window.draw(m_Sprite);
}

void Ghosts::set_pos(short x, short y)
{
    m_pos = {
        x, y
    };
}

void Ghosts::update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map)
{
    std::array<bool, 4> walls{};

    walls[Direction::Right] = map_collision(0, m_pos.x + GHOST_SPEED, m_pos.y, i_map);
    walls[Direction::Up]    = map_collision(0, m_pos.x, m_pos.y - GHOST_SPEED, i_map);
    walls[Direction::Left]  = map_collision(0, m_pos.x - GHOST_SPEED, m_pos.y, i_map);
    walls[Direction::Down]  = map_collision(0, m_pos.x, m_pos.y + GHOST_SPEED, i_map);

    unsigned char available_path = 0;

    for (unsigned a = 0; a < 4; a++)
    {
        if (a == static_cast<unsigned>(get_opposite_dir(m_direction)))
            continue;

        else if (!walls[a])
        {
            available_path++;
        }
    }

    if (available_path > 1)
    {
        Direction new_direction = static_cast<Direction>(rand() % 4);

        if (!walls[new_direction] && new_direction != get_opposite_dir(m_direction))
        {
            m_direction = new_direction;
        }
    }
    else if (walls[m_direction])
    {
        for (unsigned a = 0; a < 4; a++)
        {
            if (!walls[a] && a != static_cast<unsigned>(get_opposite_dir(m_direction)))
            {
                m_direction = static_cast<Direction>(a);
                break;
            }

        }

    }


    if (!walls[m_direction])
    {
        switch (m_direction)
        {
        case Direction::Right:
            m_pos.x += GHOST_SPEED;
            break;

        case Direction::Up:
            m_pos.y -= GHOST_SPEED;
            break;

        case Direction::Left:
            m_pos.x -= GHOST_SPEED;
            break;

        case Direction::Down:
            m_pos.y += GHOST_SPEED;
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
}