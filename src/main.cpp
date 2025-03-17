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
    std::vector<std::pair<int, int>> start_pos = {{28, 42}, {29, 42}, {30, 42}, {31, 42}, {32, 42}};    // y/x format
    for (const auto& s : start_pos) {
        grid[s.first][s.second].setFillColor(sf::Color::Cyan);
    }
}

void check_event_close(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life 2.0", sf::Style::None);
    window.setFramerateLimit(60);

    std::vector<std::vector<sf::RectangleShape>> grid(y_cells, std::vector<sf::RectangleShape>(x_cells));
    init_grid(grid);
    set_start_postion(grid);

    std::vector<std::vector<bool>> next_grid(y_cells, std::vector<bool>(x_cells));

    while (window.isOpen())
    {
        check_event_close(window);

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