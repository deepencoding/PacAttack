#include <iostream>
#include <math.h>

#include "../headers/MapCollision.hpp"
#include "../headers/Ghosts.hpp"

Ghosts::Ghosts(GHOST N)
    :m_Name(N)
{
}

void Ghosts::Draw_Ghost(sf::RenderWindow& window)
{
    m_Sprite.setPosition(m_pos.x, m_pos.y);
    if (m_Texture.loadFromFile("assets\\images\\Ghost16.png"))
    {
        m_Sprite.setTexture(m_Texture);
        m_Sprite.setTextureRect(sf::IntRect(m_XIndex * m_TextureBit, m_YIndex * m_TextureBit, m_TextureBit, m_TextureBit));
    }
    else
    {
        std::cout << "Error loading ghost texture" << std::endl;
    }

    switch (m_Name)
    {
    case GHOST::BLINKY:
        m_Sprite.setColor(sf::Color::Red);
        break;
    case GHOST::CLYDE:
        m_Sprite.setColor(sf::Color::Color (255, 182, 85, 255));
        break;
    case GHOST::PINKY:
        m_Sprite.setColor(sf::Color::Color (255, 182, 255, 255));
        break;
    case GHOST::INKY:
        m_Sprite.setColor(sf::Color::Cyan);
        break;
    default:
        break;
    }

    window.draw(m_Sprite);
}

void Ghosts::set_pos(short x, short y)
{
    m_pos = {
        x, y
    };
}

Position Ghosts::get_pos() const
{
    return m_pos;
}

void Ghosts::switch_mode()
{
    m_mode = static_cast<MODE>((m_mode + 1) % 1);
    m_direction = get_opposite_dir(m_direction);
}

bool Ghosts::pacman_collision(Position i_pacman_pos) const
{
    if (m_pos.x > i_pacman_pos.x - (CELL_SIZE / 2)
        && m_pos.x < i_pacman_pos.x + (CELL_SIZE / 2)
        && m_pos.y > i_pacman_pos.y - (CELL_SIZE / 2)
        && m_pos.y < i_pacman_pos.y + (CELL_SIZE / 2))
    {
        return true;
    }

    return false;
}

float Ghosts::get_target_dist(Direction i_dir) const
{
    short x = m_pos.x;
    short y = m_pos.y;

    switch (i_dir)
    {
    case Direction::Right:
        x += GHOST_SPEED;
        break;

    case Direction::Up:
        y -= GHOST_SPEED;
        break;

    case Direction::Left:
        x -= GHOST_SPEED;
        break;

    case Direction::Down:
        y += GHOST_SPEED;
        break;

    default:
        break;
    }

    return static_cast<float>(sqrt(pow(m_target.x - x, 2) + pow(m_target.y - y, 2)));
}

void Ghosts::reset_ghost(Position i_house, Position i_gate)
{
    m_mode = MODE::SCATTER;
    use_door = (m_Name != GHOST::BLINKY);
    m_direction = Direction::Right;
    isFrightened = 0;
    m_house = i_house;
    m_gate = i_gate;
    m_target = m_gate;
}

void Ghosts::update_target(Direction i_pacman_dir, Position i_pacman_pos, Position i_red_ghost_pos)
{
    /*if (use_door)
    {
        m_target = ;
        use_door = false;
        return;
    }*/
    if (m_mode == MODE::CHASE)
    {
        switch (m_Name)
        {
        case GHOST::BLINKY:
            m_target = i_pacman_pos;
            break;
        case GHOST::CLYDE:
            if (sqrt(pow(i_pacman_pos.x - m_pos.x, 2) + pow(i_pacman_pos.y - m_pos.y, 2))
                <= CELL_SIZE * CLYDE_DIST)
            {
                m_target = { 0 , SCREEN_HEIGHT - CELL_SIZE };
            }
            else
            {
                m_target = i_pacman_pos;
            }
            break;
        case GHOST::PINKY:
            m_target = i_pacman_pos;
            switch (i_pacman_dir)
            {
            case Direction::Right:
                m_target.x += PINKY_DIST * CELL_SIZE;
                break;

            case Direction::Up:
                m_target.y -= PINKY_DIST * CELL_SIZE;
                break;

            case Direction::Left:
                m_target.x -= PINKY_DIST * CELL_SIZE;
                break;

            case Direction::Down:
                m_target.y += PINKY_DIST * CELL_SIZE;
                break;

            default:
                break;
            }
            break;
        case GHOST::INKY:
            m_target = i_pacman_pos;
            switch (i_pacman_dir)
            {
            case Direction::Right:
                m_target.x += INKY_DIST * CELL_SIZE;
                break;

            case Direction::Up:
                m_target.y -= INKY_DIST * CELL_SIZE;
                break;

            case Direction::Left:
                m_target.x -= INKY_DIST * CELL_SIZE;
                break;

            case Direction::Down:
                m_target.y += INKY_DIST * CELL_SIZE;
                break;

            default:
                break;
            }

            m_target.x = (2 * m_target.x) - i_red_ghost_pos.x;
            m_target.y = (2 * m_target.y) - i_red_ghost_pos.y;

            break;
        default:
            break;
        }
    }
    else // SCATTER MODE
    {
        switch (m_Name)
        {
        case GHOST::BLINKY:
            m_target = { SCREEN_WIDTH - CELL_SIZE , 0 };
            break;
        case GHOST::CLYDE:
            m_target = { 0 , SCREEN_HEIGHT - CELL_SIZE };
            break;
        case GHOST::PINKY:
            m_target = { 0 , 0 };
            break;
        case GHOST::INKY:
            m_target = { SCREEN_WIDTH - CELL_SIZE , SCREEN_HEIGHT - CELL_SIZE };
            break;
        default:
            break;
        }
    }
}

void Ghosts::update(std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, Paccy& i_pacman, Ghosts& red_ghost)
{
    update_target(i_pacman.get_dir(), i_pacman.get_pos(), red_ghost.get_pos());

    std::array<bool, 4> walls{};

    walls[Direction::Right] = map_collision(0, m_pos.x + GHOST_SPEED, m_pos.y, i_map);
    walls[Direction::Up]    = map_collision(0, m_pos.x, m_pos.y - GHOST_SPEED, i_map);
    walls[Direction::Left]  = map_collision(0, m_pos.x - GHOST_SPEED, m_pos.y, i_map);
    walls[Direction::Down]  = map_collision(0, m_pos.x, m_pos.y + GHOST_SPEED, i_map);

    unsigned char available_path = 0;

    Direction optimal_dir = Direction::Undef;

    for (unsigned a = 0; a < 4; a++)
    {
        if (a == static_cast<unsigned>(get_opposite_dir(m_direction)))
            continue;

        else if (!walls[a])
        {
            if (optimal_dir == Direction::Undef)
                optimal_dir = static_cast<Direction>(a);

            available_path++;

            if (get_target_dist(static_cast<Direction>(a)) < get_target_dist(optimal_dir))
                optimal_dir = static_cast<Direction>(a);
            else if (get_target_dist(static_cast<Direction>(a)) == get_target_dist(optimal_dir))
            {
                if (static_cast<Direction>(a) == Direction::Up || optimal_dir == Direction::Up)
                    optimal_dir = Direction::Up;
                else if (static_cast<Direction>(a) == Direction::Left || optimal_dir == Direction::Left)
                    optimal_dir = Direction::Left;
                else if (static_cast<Direction>(a) == Direction::Down || optimal_dir == Direction::Down)
                    optimal_dir = Direction::Down;
            }
        }
    }

    if (available_path > 1)
    {
        bool restricted = false;
        for (unsigned iter = 0; iter < 4; iter++)
        {
            if (restricted_cells[iter] == m_pos)
            {
                restricted = true;
                break;
            }
        }
        if (!restricted)
            m_direction = optimal_dir;
    }
    else
    {
        if (optimal_dir == Direction::Undef)
            m_direction = get_opposite_dir(m_direction);
        else
            m_direction = optimal_dir;
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

    if (pacman_collision(i_pacman.get_pos()))
        std::cout << "COLLISION OCCURED" << std::endl;
}