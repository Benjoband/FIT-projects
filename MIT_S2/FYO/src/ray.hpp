/**
 * @file ray.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for Ray class and its interaction with Fiber
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef RAY_HPP
#define RAY_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class Ray
{
    public:
        Ray();
        Ray(sf::Vector2u position, sf::Vector2u size, int type);

        const sf::RectangleShape &getRay() const; // Getter for _ray

        void draw(sf::RenderWindow &window);

        void setType(int type);

        void rotateLaser(int rotation, sf::Vector2f new_position);
        void updatePosition(int direction);

        void reflection();

        void reflectionStepIndex();
        void reflectionGradedIndex();
        void reflectionSingleMode();

        void traceRefraction(int currentLayer, int nextLayer);

        void setInfrared(int infrared);

    private:
        int _fiberType;          // 0 - normal, 1 - reflection
        sf::RectangleShape _ray; // Rectangle representing the laser
        std::shared_ptr<Ray> reflectionRay = nullptr;

        float GRADED_INDEX_Y[8];
};

#endif // RAY_HPP