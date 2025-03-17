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

void set_start_postion(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<bool>>& next_grid) {
    std::vector<std::pair<int, int>> start_pos = {{28, 42}, {29, 42}, {30, 42}, {31, 42}, {32, 42}};    // y/x format
    for (const auto& s : start_pos) {
        grid[s.first][s.second].setFillColor(sf::Color::Cyan);
    }

    for (const auto& s : start_pos) {
        next_grid[s.first][s.second] = true;
    }
}

bool is_alive(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j) {
    return grid[i][j].getFillColor() == sf::Color::Cyan;
}

bool is_dead(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j) {
    return grid[i][j].getFillColor() == sf::Color::Black;
}

void update_grid(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<bool>>& next_grid) {
    for (int i = 0; i < static_cast<int>(grid.size()); ++i) {
        for (int j = 0; j < static_cast<int>(grid[i].size()); ++j) {
            int living_cells = 0;

            // Top
            if (i - 1 >= 0) {
                if (j - 1 >= 0 && is_alive(grid, i - 1, j - 1)) { living_cells += 1; }
                if (is_alive(grid, i - 1, j)) { living_cells += 1; }
                if (j + 1 < static_cast<int>(grid[i].size()) && is_alive(grid, i - 1, j + 1)) { living_cells += 1; }
            }

            // Middle
            if (j - 1 >= 0 && is_alive(grid, i, j - 1)) { living_cells += 1; }
            if (j + 1 < static_cast<int>(grid[i].size()) && is_alive(grid, i, j + 1)) { living_cells +=1; }

            // Bottom
            if (i + 1 < static_cast<int>(grid.size())) {
                if (j - 1 >= 0 && is_alive(grid, i + 1, j - 1)) { living_cells += 1; }
                if (is_alive(grid, i + 1, j)) { living_cells += 1; }
                if (j + 1 < static_cast<int>(grid[i].size()) && is_alive(grid, i + 1, j + 1)) { living_cells += 1; }
            }

            // Condition
            if (is_dead(grid, i, j) && living_cells == 3) {
                next_grid[i][j] = true;
            }
            if (is_alive(grid, i, j) && living_cells < 2) {
                next_grid[i][j] = false;
            }
            if (is_alive(grid, i, j) && living_cells > 3) {
                next_grid[i][j] = false;
            }
        }
    }
}


void check_events(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life 2.0", sf::Style::None);
    window.setFramerateLimit(144);

    std::vector<std::vector<sf::RectangleShape>> grid(y_cells, std::vector<sf::RectangleShape>(x_cells));
    init_grid(grid);
    std::vector<std::vector<bool>> next_grid(y_cells, std::vector<bool>(x_cells));
    set_start_postion(grid, next_grid);

    sf::Clock clock;
    constexpr sf::Time delay = sf::seconds(0.25f);

    while (window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();

        check_events(window);
        if (elapsed >= delay) {
            update_grid(grid, next_grid);
            clock.restart();
        }

        window.clear();
        for (const auto& s : grid) {
            for (const auto& j : s) {
                window.draw(j);
            }
        }
        window.display();

        for (int i = 0; i < static_cast<int>(grid.size()); ++i) {
            for (int j = 0; j < static_cast<int>(grid[i].size()); ++j) {
                if (next_grid[i][j]) {
                    grid[i][j].setFillColor(sf::Color::Cyan);
                } else {
                    grid[i][j].setFillColor(sf::Color::Black);
                }
            }
        }
    }

    return 0;
}