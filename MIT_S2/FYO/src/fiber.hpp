/**
 * @file laser.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Class representing laser
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef FIBER_HPP
#define FIBER_HPP

#include "core.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Class representing
 *
 */
class Fiber
{
    public:
        Fiber();
        Fiber(sf::Vector2u corePos, sf::Vector2u coreSize, sf::Vector2u claddingTopPos,
              sf::Vector2u claddingBotPos, sf::Vector2u claddingTopSize,
              sf::Vector2u claddingBotSize, int type);

        /**
         * @brief Draws the laser
         *
         * @param window
         */
        void draw(sf::RenderWindow &window);

        void setType(int type);

    private:
        int _type;
        Core _core;

        sf::RectangleShape _claddingStepIndexTop;
        sf::RectangleShape _claddingStepIndexBot;

        sf::RectangleShape _claddingGradedIndexTop;
        sf::RectangleShape _claddingGradedIndexBot;
        std::vector<sf::RectangleShape> _stepindexCladding; // representation of step index cladding

        sf::RectangleShape _singleModeCladdingTop;
        sf::RectangleShape _singleModeCladdingBot;
};

#endif // FIBER_HPP