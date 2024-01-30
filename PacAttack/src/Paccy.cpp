#include <iostream>

#include "../headers/Paccy.hpp"
#include "../headers/MapCollision.hpp"

Paccy::Paccy()
{
    m_dead = false;
    m_direction = Direction::Right;
    energized = false;
    energizer_timer = 0;
    m_animation_over = false;

}

void Paccy::Draw_Paccy(bool i_game_won, sf::RenderWindow& window, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map)
{
    unsigned char frame = static_cast<unsigned char>(floor(animation_timer / (unsigned short)PACMAN_ANIMATION_SPEED));

    m_Sprite.setPosition(m_pos.x, m_pos.y);

    if (m_dead || i_game_won)
    {
        if (animation_timer < PACMAN_ANIMATION_SPEED * PACMAN_DEATH_FRAMES)
        {
            animation_timer++;
            m_Texture.loadFromFile("assets\\images\\PacmanDeath16.png");
            m_Sprite.setTexture(m_Texture);
            m_Sprite.setTextureRect(sf::IntRect(frame * TEXTURE_BIT, 0, TEXTURE_BIT, TEXTURE_BIT));
            window.draw(m_Sprite);
        }
        else
        {
            m_animation_over = true;
        }
    }
    else
    {
        m_Texture.loadFromFile("assets\\images\\Pacman16.png");
        m_Sprite.setTexture(m_Texture);
        m_Sprite.setTextureRect(sf::IntRect(frame * TEXTURE_BIT, m_direction * TEXTURE_BIT, TEXTURE_BIT, TEXTURE_BIT));
        window.draw(m_Sprite);
        std::array<bool, 4> walls{};

        walls[Direction::Right] = map_collision(0, 0, m_pos.x + PACMAN_SPEED, m_pos.y, i_map);
        walls[Direction::Up] = map_collision(0, 0, m_pos.x, m_pos.y - PACMAN_SPEED, i_map);
        walls[Direction::Left] = map_collision(0, 0, m_pos.x - PACMAN_SPEED, m_pos.y, i_map);
        walls[Direction::Down] = map_collision(0, 0, m_pos.x, m_pos.y + PACMAN_SPEED, i_map);

        if (!walls[m_direction])
        {
            animation_timer = (animation_timer + 1) % ((unsigned short)(PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED));
        }
    }    
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

void Paccy::set_dead(bool i_dead)
{
    m_dead = i_dead;
    std::cout << "PACMAN DEAD" << std::endl;
}

bool Paccy::get_dead() const
{
    return m_dead;
}

unsigned short Paccy::get_energizer_timer()
{
    return energizer_timer;
}

bool Paccy::get_animation_over() const
{
    return m_animation_over;
}

bool Paccy::get_energy() const
{
    return energized;
}

void Paccy::reset_pacman()
{
    m_dead = false;
    m_direction = Direction::Right;
    energized = false;
    energizer_timer = 0;
    m_animation_over = false;
}

void Paccy::update(unsigned char curr_lvl, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, GhostManager& i_ghost_manager, float curr_fps)
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
        energized = true;
        energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, curr_lvl));
        i_ghost_manager.pause_clock();
        // i_ghost_manager.set_wave_timer(i_ghost_manager.get_wave_timer().asSeconds() + (float)(energizer_timer / curr_fps));
        // i_ghost_manager.switch_frightened();
    }
    else
    {
        // energizer_timer = std::max(0, energizer_timer - 1);
        if (energized == true)
        {
            energizer_timer = std::max(energizer_timer - 1, 0);
            if (energizer_timer == 0)
            {
                i_ghost_manager.resume_clock();
                energized = false;
                //i_ghost_manager.switch_frightened();
            }
        }
    }
    // std::cout << energized << std::endl;
}