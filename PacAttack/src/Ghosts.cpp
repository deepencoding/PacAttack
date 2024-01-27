#include <iostream>
#include <math.h>

#include "../headers/MapCollision.hpp"
#include "../headers/Ghosts.hpp"

Ghosts::Ghosts(GHOST N)
    :m_Name(N), isFrightened(FRIGHT::NONE), speed(GHOST_SPEED)
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

    if (isFrightened == FRIGHT::LITTLE)
    {
        m_Sprite.setColor(sf::Color::Color(36, 36, 255, 255));
        
    }
    else {
        switch (m_Name)
        {
        case GHOST::BLINKY:
            m_Sprite.setColor(sf::Color::Red);
            break;
        case GHOST::CLYDE:
            m_Sprite.setColor(sf::Color::Color(255, 182, 85, 255));
            break;
        case GHOST::PINKY:
            m_Sprite.setColor(sf::Color::Color(255, 182, 255, 255));
            break;
        case GHOST::INKY:
            m_Sprite.setColor(sf::Color::Cyan);
            break;
        default:
            break;
        }
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

GHOST Ghosts::get_name() const
{
    return m_Name;
}

void Ghosts::switch_mode()
{
    // m_mode = static_cast<MODE>(((unsigned)m_mode + 1) % 1);
    if (m_mode == MODE::CHASE)
    {
        m_mode = MODE::SCATTER;
    }
    else
    {
        m_mode = MODE::CHASE;
    }
    m_direction = get_opposite_dir(m_direction);
}

void Ghosts::switch_frightened()
{
    if (isFrightened == FRIGHT::NONE)
    {
        isFrightened = FRIGHT::LITTLE;
    }
    else if (isFrightened == FRIGHT::LITTLE)
    {
        isFrightened = FRIGHT::NONE;
    }
    m_direction = get_opposite_dir(m_direction);
}

MODE Ghosts::get_mode() const
{
    return m_mode;
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
    isFrightened = FRIGHT::NONE;
    fright_speed_timer = 0;
    m_house = i_house;
    m_gate = i_gate;
    m_target = m_gate;
}

void Ghosts::update_target(Direction i_pacman_dir, Position i_pacman_pos, Position i_red_ghost_pos)
{
    if (use_door)
    {
        if (m_pos == m_target)
        {
            if (m_target == m_gate)
            {
                use_door = false;
                // speed = GHOST_SPEED;
            }
            else if (m_target == m_house)
            {
                isFrightened = FRIGHT::NONE;
                m_target = m_gate;
            }
        }
    }
    else 
    {
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
}

void Ghosts::update(unsigned char curr_lvl, std::array < std::array < Cell, MAP_WIDTH >, MAP_HEIGHT >& i_map, Paccy& i_pacman, Ghosts& red_ghost)
{
    update_target(i_pacman.get_dir(), i_pacman.get_pos(), red_ghost.get_pos());

    //if (m_Name == GHOST::BLINKY)
    //{
    //    std::cout << isFrightened << std::endl;
    //    std::cout << "X= " << m_target.x << "Y= " << m_target.y << std::endl;
    //    std::cout << m_mode << std::endl;
    //}

    bool to_move = false;
    speed = GHOST_SPEED;

    std::array<bool, 4> walls{};
    walls[Direction::Right] = map_collision(use_door, 0, m_pos.x + GHOST_SPEED, m_pos.y, i_map);
    walls[Direction::Up]    = map_collision(use_door, 0, m_pos.x, m_pos.y - GHOST_SPEED, i_map);
    walls[Direction::Left]  = map_collision(use_door, 0, m_pos.x - GHOST_SPEED, m_pos.y, i_map);
    walls[Direction::Down]  = map_collision(use_door, 0, m_pos.x, m_pos.y + GHOST_SPEED, i_map);

    // to make the ghost little fightened or not
    if (isFrightened == FRIGHT::NONE && i_pacman.get_energizer_timer() == static_cast<unsigned short>(ENERGIZER_DURATION/pow(2, curr_lvl)))
    {
        isFrightened = FRIGHT::LITTLE;
        fright_speed_timer = GHOST_FRIGHTENED_WAIT;
        m_direction = get_opposite_dir(m_direction);
    }
    else if (i_pacman.get_energizer_timer() == 0 && isFrightened == FRIGHT::LITTLE)
    {
        isFrightened = FRIGHT::NONE;
        m_direction = get_opposite_dir(m_direction);
    }

    if (isFrightened == FRIGHT::FULLY && m_pos.x % GHOST_ESCAPE_SPEED == 0 && m_pos.y % GHOST_ESCAPE_SPEED == 0)
    {
        speed = GHOST_ESCAPE_SPEED;
    }

    unsigned char available_path = 0;
    if (isFrightened != FRIGHT::LITTLE)
    {
        to_move = true;
        Direction optimal_dir = Direction::Undef;

        for (unsigned a = 0; a < 4; a++)
        {
            if (a == static_cast<unsigned>(get_opposite_dir(m_direction)))
                continue;

            else if (!walls[a])
            {
                if (optimal_dir == Direction::Undef)
                {
                    optimal_dir = static_cast<Direction>(a);
                }

                available_path++;

                if (get_target_dist(static_cast<Direction>(a)) < get_target_dist(optimal_dir))
                {
                    optimal_dir = static_cast<Direction>(a);
                }
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
                if (restricted_cells[iter] == m_pos && m_direction != Direction::Down)
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
    }
    else
    {
        // RANDOM DIRECTIONS WHEN RUNNING AWAY
        if (fright_speed_timer == 0)
        {
            to_move = true;

            fright_speed_timer = GHOST_FRIGHTENED_WAIT;

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
                Direction new_direction = static_cast<Direction>(rand() % 4); // randomness

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
        }
        else 
        {
            fright_speed_timer--;
        }
    }

        // =================================================================================================
        /*unsigned char available_path = 0;
        Direction random_direction = (Direction)(rand() % 4);

        if (fright_speed_timer == 0)
        {
            to_move = true;

            fright_speed_timer = GHOST_FRIGHTENED_WAIT;

            for (unsigned char a = 0; a < 4; a++)
            {
                //They can't turn back even if they're frightened.
                if (a == (unsigned char) get_opposite_dir(m_direction))
                {
                    continue;
                }
                else if (!walls[a])
                {
                    available_path++;
                }
            }

            if (available_path > 0)
            {
                while (walls[random_direction] || random_direction == () get_opposite_dir(m_direction))
                {
                    //We keep picking a random direction until we can use it.
                    random_direction = rand() % 4;
                }

                m_direction = (Direction)random_direction;
            }
            else
            {
                //If there's no other way, it turns back.
                m_direction = get_opposite_dir(m_direction);
            }
        }
        else
        {
            fright_speed_timer--;
        }*/
        // =========================================================================================

    // std::cout << to_move << std::endl;
    /*if (m_Name == GHOST::BLINKY)
        std::cout << m_direction << std::endl;*/
    if (to_move)
    {
        if (!walls[m_direction])
        {
            switch (m_direction)
            {
            case Direction::Right:
                m_pos.x += speed;
                break;

            case Direction::Up:
                m_pos.y -= speed;
                break;

            case Direction::Left:
                m_pos.x -= speed;
                break;

            case Direction::Down:
                m_pos.y += speed;
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

    if (pacman_collision(i_pacman.get_pos()))
    {
        if (isFrightened == FRIGHT::NONE)
        {
            i_pacman.set_dead(true);
        }
        else
        {
            use_door = true;
            isFrightened = FRIGHT::FULLY;
            m_target = m_house;
        }
    }
}