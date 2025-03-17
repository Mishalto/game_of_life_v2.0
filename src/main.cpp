#include <SFML/Graphics.hpp>
#include <Constants.hpp>
#include <iostream>
#include <array>
#include <thread>

void init_grid(std::vector<std::vector<sf::RectangleShape>>& grid) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            grid[i][j].setFillColor(sf::Color::Black);
            grid[i][j].setSize({cell_size, cell_size});
            grid[i][j].setPosition({static_cast<float>(j) * cell_size,
                                    static_cast<float>(i) * cell_size});
        }
    }
}

void set_start_postion(std::vector<std::vector<sf::RectangleShape>>& grid) {
    std::vector<std::pair<int, int>> start_pos = {{20, 13}, {20, 14}, {20, 15}, {20, 16}, {20, 17}};
    for (const auto& s : start_pos) {
        grid[s.second][s.first].setFillColor(sf::Color::Cyan);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life 2.0", sf::Style::None);
    window.setFramerateLimit(30);

    std::vector<std::vector<sf::RectangleShape>> grid(y_cells, std::vector<sf::RectangleShape>(x_cells));
    init_grid(grid);
    set_start_postion(grid);

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