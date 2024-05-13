#include "Utils.hpp"

float norm(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}