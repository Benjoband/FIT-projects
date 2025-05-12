/**
 * @file laser.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Class representing laser
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef LASER_HPP
#define LASER_HPP

#include "ray.hpp"
#include <SFML/Graphics.hpp>

/**
 * @brief Class representing
 *
 */
class Laser
{
    public:
        Laser();
        Laser(sf::Vector2u position, sf::Vector2u size);

        /**
         * @brief Updates the rotation of the laser
         *
         * @param rotation
         */
        void updateRotation(int rotation, Ray &ray);

        /**
         * @brief Updates the position of the laser
         *
         * @param direction
         */
        void updatePosition(int direction);

        /**
         * @brief Draws the laser
         *
         * @param window
         */
        void draw(sf::RenderWindow &window);

        // getters

        /**
         * @brief Returns the position of the laser
         *
         * @return sf::Vector2f
         */
        sf::Vector2f getPosition() const;

        /**
         * @brief Returns the rotation of the laser
         *
         * @return int degrees
         */
        int getRotation() const;

    private:
        sf::RectangleShape _laser; // Rectangle representing the laser
};

#endif // LASER_HPP