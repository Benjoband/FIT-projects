/**
 * @file laser.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief  Implementation of the Laser class
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "laser.hpp"
#include <cmath>
#include <iostream>

#include "config.hpp"

Laser::Laser(sf::Vector2u position, sf::Vector2u size)
{
    _laser = sf::RectangleShape(sf::Vector2f(size.x, size.y));
    _laser.setPosition(sf::Vector2f(position.x, position.y));
    _laser.setFillColor(sf::Color(192, 192, 192, 255));
    _laser.setOutlineColor(sf::Color::Black);
    _laser.setOutlineThickness(size.y / 50);
    _laser.setOrigin(sf::Vector2f(0, size.y / 2)); // sets the origin to the left side of the
    // laser
}

Laser::Laser() : _laser(sf::RectangleShape(sf::Vector2f(config::LASER_WIDTH, config::LASER_HEIGHT)))
{
    _laser.setPosition(sf::Vector2f(config::LASER_X, config::LASER_Y));
    _laser.setFillColor(sf::Color(192, 192, 192, 255));
    _laser.setOutlineColor(sf::Color::Black);
    _laser.setOutlineThickness(config::LASER_HEIGHT / 50);
    _laser.setOrigin(sf::Vector2f(0, config::LASER_HEIGHT / 2));
}

void Laser::updateRotation(int rotation, Ray &ray)
{
    sf::Angle angle = sf::degrees(rotation) + _laser.getRotation();

    if (int(angle.asDegrees()) == 45)
    {
        angle = sf::degrees(44);
        rotation = 0;
    }
    if (int(angle.asDegrees()) == 316)
    {
        angle = sf::degrees(317);
        rotation = 0;
    }
    _laser.setRotation(angle);
    sf::Vector2f laserPosition = _laser.getPosition();

    float newX = laserPosition.x + _laser.getSize().x * cos(angle.asRadians());
    float newY = laserPosition.y + _laser.getSize().x * sin(angle.asRadians());

    ray.rotateLaser(rotation, sf::Vector2f(newX, newY));
}

void Laser::updatePosition(int direction) { _laser.move(sf::Vector2f(direction, 0)); }

void Laser::draw(sf::RenderWindow &window) { window.draw(_laser); }

sf::Vector2f Laser::getPosition() const { return _laser.getPosition(); }

int Laser::getRotation() const { return _laser.getRotation().asDegrees(); }