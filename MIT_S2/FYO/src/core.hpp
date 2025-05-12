/**
 * @file core.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for Core class and classes derived from it
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Graphics.hpp>

class Core
{
    public:
        Core();
        Core(sf::Vector2u position, sf::Vector2u size);
        virtual void draw(sf::RenderWindow &window);

    private:
        sf::RectangleShape _core;
};

#endif // CORE_HPP