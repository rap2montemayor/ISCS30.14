#ifndef SRC_MATH_HPP_
#define SRC_MATH_HPP_

#include <cmath>

#include <SFML/Graphics.hpp>

float getLength(const sf::Vector2f& vec);
void normalize(sf::Vector2f& vec);
float dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
float getAngle(sf::Vector2f v1, sf::Vector2f v2);

#endif // SRC_MATH_HPP_
