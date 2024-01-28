#include <SFML/Graphics.hpp>

#include "../headers/DrawText.hpp"
#include "../headers/global.hpp"


void DrawText(const std::string& i_text, sf::RenderWindow& i_win, bool i_center, short i_x, short i_y)
{
    int HIGH_SCORE = 0;

    sf::Text text;
    sf::Font font;
    font.loadFromFile("assets\\font\\Emulogic-zrEw.ttf");

    text.setFont(font);
    text.setString(sf::String(i_text));
    text.setCharacterSize(CELL_SIZE);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    text.setPosition(sf::Vector2f(i_x * CELL_SIZE, i_y * CELL_SIZE));
    

    if (i_center)
    {
        //center text
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
    }

    i_win.draw(text);
}
