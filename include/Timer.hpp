#pragma once

#include <SFML/Graphics.hpp>

class Timer {
private:
    sf::Clock timer_;
    sf::Time elapsed_time_;

    sf::Time delay_;
public:
    Timer(float delay);

    void start();
    bool is_time_elapsed();
};