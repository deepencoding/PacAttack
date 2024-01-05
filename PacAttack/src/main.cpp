#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/global.hpp"

int main()
{
    // ========================= Initialize game =========================
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(672, 704), "PacAttack - Pacman Clone", sf::Style::Close, settings);

    // ========================= Load assets =========================
    sf::Texture pacmanTexture;
    sf::Sprite pacmanSprite;
    if (pacmanTexture.loadFromFile("C:\\Dev\\Projects\\PacAttack\\PacAttack\\assets\\images\\Pacman16.png"))
    {
        std::cout << "Pacman texture loaded successfully" << std::endl;
        pacmanSprite.setTexture(pacmanTexture);
        int pacmanXIndex = 0;
        int pacmanYIndex = 0;
        int textureBit = 16;
        pacmanSprite.setTextureRect(sf::IntRect(pacmanXIndex * textureBit, pacmanYIndex * textureBit, textureBit, textureBit));
    }
    else
    {
		std::cout << "Error loading pacman texture" << std::endl;
	}

    // ========================= Main game loop =========================
    while (window.isOpen())
    {
        // ========================= Event loop =========================
        sf::Event event;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			pacmanSprite.move(-1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            pacmanSprite.move(1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pacmanSprite.move(0.f, -1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            pacmanSprite.move(0.f, 1.f);

        window.clear();
        // ========================= Render or Draw =========================
        window.draw(pacmanSprite);
        window.display();
    }

    return 0;
}