#include <SFML/Graphics.hpp>
#include <Constants.hpp>
#include <iostream>
#include <array>

int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life 2.0", sf::Style::None);
    window.setFramerateLimit(60);

    std::array<std::array<sf::RectangleShape, x_cells>, y_cells> grid;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }
}