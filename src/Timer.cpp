#include <Timer.hpp>

Timer::Timer(float delay) {
    delay_ = sf::seconds(delay);
}

void Timer::start() {
    elapsed_time_ = timer_.getElapsedTime();
}

bool Timer::is_time_elapsed() {
    if (elapsed_time_ >= delay_) {
        timer_.restart();
        return true;
    }

    return false;
}