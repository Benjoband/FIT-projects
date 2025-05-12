/**
 * @file ray.cpp
 * @author Alexej Beňuš xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of Ray class and its interaction with Fiber
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "ray.hpp"
#include "config.hpp"
#include <cmath>
#include <iostream>

Ray::Ray()
    : _ray(sf::RectangleShape(sf::Vector2f(config::RAY_WIDTH, config::RAY_HEIGHT))), _fiberType(0)
{
    _ray.setPosition(sf::Vector2f(config::LASER_X + config::LASER_WIDTH, config::LASER_Y));
    _ray.setFillColor(sf::Color::Red);
};

Ray::Ray(sf::Vector2u position, sf::Vector2u size, int type)
    : _ray(sf::RectangleShape(sf::Vector2f(size.x, size.y)))
{
    _ray.setPosition(sf::Vector2f(position.x, position.y));
    _ray.setFillColor(sf::Color::Red);
    _fiberType = type;
}

const sf::RectangleShape &Ray::getRay() const { return _ray; }

void Ray::draw(sf::RenderWindow &window)
{
    window.draw(getRay()); // Use the getter to draw the current ray

    // Draw the reflection rays if they exist
    std::shared_ptr<Ray> currentRay = reflectionRay;
    while (currentRay != nullptr)
    {
        window.draw(currentRay->getRay()); // Use the getter for reflection rays
        currentRay = currentRay->reflectionRay;
    }
}
void Ray::rotateLaser(int rotation, sf::Vector2f new_position)
{
    sf::Angle angle = sf::degrees(rotation) + _ray.getRotation();
    _ray.setRotation(angle);
    _ray.setPosition(new_position);
}

void Ray::updatePosition(int direction)
{
    _ray.setPosition(sf::Vector2f(_ray.getPosition().x + direction, _ray.getPosition().y));
}

void Ray::setType(int type) { _fiberType = type; }

void Ray::reflection()
{
    std::cout << "Fiber type: " << _fiberType << "\n";
    if (_ray.getRotation().asDegrees() == 0)
    {
        std::cout << "Ray is horizontal, no reflection.\n";
        return;
    }
    switch (_fiberType)
    {
    case 0:
        reflectionStepIndex();
        break;
    case 1:
        reflectionGradedIndex();
        break;
    case 2:
        reflectionSingleMode();
        break;
    default:
        break;
    }
}

void Ray::reflectionStepIndex()
{
    float topY = config::SCREEN_HEIGHT / 2 - config::CORE_STEP_INDEX_HEIGHT / 2;
    float bottomY = config::SCREEN_HEIGHT / 2 + config::CORE_STEP_INDEX_HEIGHT / 2;

    sf::Vector2f pos = _ray.getPosition();
    float angleRad = _ray.getRotation().asRadians();

    if (pos.x >= config::CABLE_END_X)
        return;

    float reflectY;
    if (std::sin(angleRad) < 0)
    {
        reflectY = topY;
        std::cout << "Reflecting from TOP at Y = " << reflectY << "\n";
    }
    else
    {
        reflectY = bottomY;
        std::cout << "Reflecting from BOTTOM at Y = " << reflectY << "\n";
    }

    float height = std::abs(reflectY - pos.y);
    float dx = std::abs(height / std::tan(angleRad));
    float intersectX = pos.x + dx;

    if (intersectX >= config::CABLE_END_X)
        intersectX = config::CABLE_END_X;

    sf::Vector2f intersection(intersectX, reflectY);
    std::cout << "Intersection at: (" << intersection.x << ", " << intersection.y << ")\n";

    float rayLength = std::sqrt(dx * dx + height * height);
    _ray.setSize({rayLength, 2});

    float newAngleRad = -angleRad;
    float newAngleDeg = newAngleRad * 180.0f / 3.14159265f;

    reflectionRay = std::make_shared<Ray>();
    reflectionRay->_ray.setSize({rayLength, 2});
    reflectionRay->_ray.setFillColor(sf::Color::Red);
    reflectionRay->_ray.setPosition(intersection);
    reflectionRay->_ray.setRotation(sf::degrees(newAngleDeg));
    reflectionRay->_fiberType = 0;

    std::cout << "Created reflection ray at angle: " << newAngleDeg << ", length: " << rayLength
              << "\n";

    if (intersection.x < config::CABLE_END_X)
    {
        reflectionRay->reflectionStepIndex();
    }
}

void Ray::reflectionSingleMode()
{
    float topY = config::SCREEN_HEIGHT / 2 - config::CORE_SINGLE_MODE_HEIGHT / 2;
    float bottomY = config::SCREEN_HEIGHT / 2 + config::CORE_SINGLE_MODE_HEIGHT / 2;

    sf::Vector2f pos = _ray.getPosition();
    float angleRad = _ray.getRotation().asRadians();

    if (pos.x >= config::CABLE_END_X)
        return;

    float reflectY;
    if (std::sin(angleRad) < 0)
    {
        reflectY = topY;
        std::cout << "Reflecting from TOP at Y = " << reflectY << "\n";
    }
    else
    {
        reflectY = bottomY;
        std::cout << "Reflecting from BOTTOM at Y = " << reflectY << "\n";
    }

    float height = std::abs(reflectY - pos.y);
    float dx = std::abs(height / std::tan(angleRad));
    float intersectX = pos.x + dx;

    if (intersectX >= config::CABLE_END_X)
        intersectX = config::CABLE_END_X;

    sf::Vector2f intersection(intersectX, reflectY);
    std::cout << "Intersection at: (" << intersection.x << ", " << intersection.y << ")\n";

    float rayLength = std::sqrt(dx * dx + height * height);
    _ray.setSize({rayLength, 2});

    float newAngleRad = -angleRad;
    float newAngleDeg = newAngleRad * 180.0f / 3.14159265f;

    reflectionRay = std::make_shared<Ray>();
    reflectionRay->_ray.setSize({rayLength, 2});
    reflectionRay->_ray.setFillColor(sf::Color::Red);
    reflectionRay->_ray.setPosition(intersection);
    reflectionRay->_ray.setRotation(sf::degrees(newAngleDeg));
    reflectionRay->_fiberType = 1;

    std::cout << "Created reflection ray at angle: " << newAngleDeg << ", length: " << rayLength
              << "\n";

    if (intersection.x < config::CABLE_END_X)
    {
        reflectionRay->reflectionSingleMode();
    }
}

void Ray::reflectionGradedIndex()
{
    sf::Vector2f pos = _ray.getPosition();
    float angleRad = _ray.getRotation().asRadians();

    if (pos.x >= config::CABLE_END_X)
        return;

    // Find the first intersection with one of the layer boundaries
    int layerCrossed = -1;
    float closestX = std::numeric_limits<float>::max();
    float intersectY = 0.0f;

    for (int i = 0; i < 10; ++i) // 10 layers now including cladding
    {
        float deltaY = config::GRADED_INDEX_Y[i] - pos.y;
        float tanAngle = std::tan(angleRad);

        if (std::abs(tanAngle) < 1e-6)
            continue; // avoid division by zero

        float dx = deltaY / tanAngle;
        float intersectionX = pos.x + dx;

        if (intersectionX > pos.x && intersectionX < closestX && intersectionX > 384)
        {
            closestX = intersectionX;
            layerCrossed = i;
            intersectY = config::GRADED_INDEX_Y[i];
        }
    }

    if (layerCrossed != -1)
    {
        std::cout << "First intersection at layer " << layerCrossed << " with Y = " << intersectY
                  << ", X = " << closestX << "\n";

        // Compute and apply distance to current ray
        sf::Vector2f delta = {closestX - pos.x, intersectY - pos.y};
        float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        _ray.setSize({distance, 2});

        // Handle reflection at cladding boundaries
        if (layerCrossed == 0 || layerCrossed == 9)
        {
            std::cout << "Ray hit cladding boundary (layer " << layerCrossed << "). Reflecting.\n";
            float flippedAngle = 360.0f - _ray.getRotation().asDegrees();

            sf::Vector2u raySize = {1000, 2};
            sf::Vector2u intersectionPoint = sf::Vector2u(closestX, intersectY);
            reflectionRay = std::make_shared<Ray>(intersectionPoint, raySize, 0);
            reflectionRay->_ray.setRotation(sf::degrees(flippedAngle));
            reflectionRay->_ray.setFillColor(sf::Color::Red);
            reflectionRay->_fiberType = 1;

            if (closestX < 1920)
                reflectionRay->reflectionGradedIndex();
            return;
        }

        // Else: refraction using Snell's law
        float angleDeg = _ray.getRotation().asDegrees();

        // Adjust angle to [0–45] range for incidence
        if (angleDeg >= 315.0f && angleDeg < 360.0f)
            angleDeg = 360.0f - angleDeg;

        float incidenceAngleRad = angleDeg * (3.14159265f / 180.0f);
        int directionSign = (_ray.getRotation().asDegrees() > 270) ? 1 : -1;

        int currentLayer = (directionSign == 1) ? layerCrossed - 1 : layerCrossed + 1;
        int nextLayer = layerCrossed;

        if (currentLayer < 0 || currentLayer >= 10 || nextLayer < 0 || nextLayer >= 10)
            return;

        float n1 = config::GRADED_INDEX_REFRACTION[currentLayer];
        float n2 = config::GRADED_INDEX_REFRACTION[nextLayer];

        float sinIncidence = std::sin(incidenceAngleRad);
        float sinRefraction = (n1 / n2) * sinIncidence;

        if (std::abs(sinRefraction) > 1.0f)
        {
            std::cout << "Total internal reflection occurred.\n";
            return;
        }

        float refractionAngleRad = std::asin(sinRefraction);
        float refractionAngleDeg = refractionAngleRad * (180.0f / 3.14159265f);

        float newAngleDeg = (_ray.getRotation().asDegrees() >= 315.0f) ? 360.0f - refractionAngleDeg
                                                                       : refractionAngleDeg;

        sf::Vector2u raySize = {1000, 2};
        sf::Vector2u intersectionPoint = sf::Vector2u(closestX, intersectY);
        reflectionRay = std::make_shared<Ray>(intersectionPoint, raySize, 0);
        reflectionRay->_ray.setRotation(sf::degrees(newAngleDeg));
        reflectionRay->_ray.setFillColor(sf::Color::Red);
        reflectionRay->_fiberType = 1;

        if (closestX < 1920)
            reflectionRay->reflectionGradedIndex();
    }
    else
    {
        std::cout << "No layer intersection found in current direction." << std::endl;
    }
}

void Ray::setInfrared(int infrared)
{
    if (infrared)
    {
        _ray.setFillColor(sf::Color(255, 0, 0, 0));
        while (reflectionRay != nullptr)
        {
            reflectionRay->_ray.setFillColor(sf::Color(255, 0, 0, 255));
            reflectionRay = reflectionRay->reflectionRay;
        }
    }
    else
    {
        _ray.setFillColor(sf::Color(255, 0, 0, 255));
        while (reflectionRay != nullptr)
        {
            reflectionRay->_ray.setFillColor(sf::Color(255, 0, 0, 255));
            reflectionRay = reflectionRay->reflectionRay;
        }
    }
}