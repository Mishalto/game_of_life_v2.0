#include <SFML/Graphics.hpp>
#include <Constants.hpp>
#include <iostream>
#include <array>
#include <thread>

void init_grid(std::vector<std::vector<sf::RectangleShape>>& grid) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            grid[i][j].setFillColor(sf::Color::White);
            grid[i][j].setSize({cell_size, cell_size});
            grid[i][j].setPosition({static_cast<float>(j) * cell_size,
                                    static_cast<float>(i) * cell_size});
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life 2.0", sf::Style::None);
    window.setFramerateLimit(30);

    std::vector<std::vector<sf::RectangleShape>> grid(y_cells, std::vector<sf::RectangleShape>(x_cells));
    init_grid(grid);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        for (const auto& s : grid) {
            for (const auto& j : s) {
                window.draw(j);
            }
        }
        window.display();
    }

    return 0;
}