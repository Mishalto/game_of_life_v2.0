#include <SFML/Graphics.hpp>
#include <Constants.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <thread>

#include <Timer.hpp>

// Forward dec for convenience
bool is_alive(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j);
bool is_dead(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j);
int count_living_neighbors(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j);

// Service
void init_grid(std::vector<std::vector<sf::RectangleShape>>& grid) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            grid[i][j].setFillColor(sf::Color::Black);
            grid[i][j].setSize({cell_size, cell_size});
            grid[i][j].setPosition({static_cast<float>(j) * cell_size, static_cast<float>(i) * cell_size});
        }
    }
}
void copy_grid(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<bool>>& next_grid) {
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
void draw_grid(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>& grid) {
    for (const auto& s : grid) {
        for (const auto& j : s) {
            if (j.getFillColor() == sf::Color::Cyan) {
                window.draw(j);
            }
        }
    }
}

void set_start_postion(std::vector<std::vector<bool>>& next_grid) {
    std::vector<std::pair<int, int>> start_pos = {{20, 13}, {20, 14}, {20, 15}, {20, 16}, {20, 17}};

    for (const auto& s : start_pos) {
        next_grid[s.first][s.second] = true;
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

// Logic
void update_grid(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<bool>>& next_grid) {
    for (int i = 0; i < static_cast<int>(grid.size()); ++i) {
        for (int j = 0; j < static_cast<int>(grid[i].size()); ++j) {
            int living_cells = count_living_neighbors(grid, i, j);

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

int count_living_neighbors(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j) {
    constexpr int directions_count = 8;
    static const std::array<std::pair<int, int>, directions_count> directions = {{
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    }};
    int living_cells = 0;
    for (const auto& [di, dj] : directions) {
        int ni = di + i;
        int nj = dj + j;
        if ((ni >= 0 && ni < static_cast<int>(grid.size()) &&
            nj >= 0 && nj < static_cast<int>(grid.size()))
            && is_alive(grid, ni, nj)) {
                living_cells += 1;
            }
    }

    return living_cells;
}

bool is_alive(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j) {
    return grid[i][j].getFillColor() == sf::Color::Cyan;
}
bool is_dead(const std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j) {
    return grid[i][j].getFillColor() == sf::Color::Black;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life 2.0", sf::Style::None);
    window.setFramerateLimit(144);

    std::vector<std::vector<sf::RectangleShape>> grid(y_cells, std::vector<sf::RectangleShape>(x_cells));
    init_grid(grid);
    std::vector<std::vector<bool>> next_grid(y_cells, std::vector<bool>(x_cells));
    set_start_postion(next_grid);

    Timer timer(0.2f);

    while (window.isOpen())
    {
        timer.start();
        copy_grid(grid, next_grid);
        check_events(window);

        if (timer.is_time_elapsed()) {
            update_grid(grid, next_grid);
        }

        window.clear();
        draw_grid(window, grid);
        window.display();
    }

    return 0;
}