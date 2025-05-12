/**
 * @file core.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of Core class
 * @version 0.1
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "core.hpp"
#include "config.hpp"

Core::Core() : _core(sf::Vector2f(config::CORE_WIDTH, config::CORE_HEIGHT))
{
    _core.setPosition(sf::Vector2f(config::CORE_X, config::CORE_Y));
    _core.setFillColor(sf::Color(211, 211, 211, 255));
}
Core::Core(sf::Vector2u position, sf::Vector2u size)
{
    _core = sf::RectangleShape(sf::Vector2f(size.x, size.y));
    _core.setPosition(sf::Vector2f(position.x, position.y));
    _core.setFillColor(sf::Color(211, 211, 211, 255));
}

void Core::draw(sf::RenderWindow &window) { window.draw(_core); }
