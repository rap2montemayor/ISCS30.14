#include "Math.hpp"

#include <iostream>

float getLength(const sf::Vector2f& vec) {
    return std::sqrt( (vec.x * vec.x) + (vec.y * vec.y) );
}

void normalize(sf::Vector2f& vec) {
    float len = getLength(vec);
    const float eps = 1e-6;
    if (len > eps) {
        vec.x /= len;
        vec.y /= len;
    } else {
        vec.x = 0;
        vec.y = 0;
    }
}

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}


float getAngle(sf::Vector2f v1, sf::Vector2f v2) {
    normalize(v1);
    normalize(v2);
    return std::acos(dot(v1, v2));
}
