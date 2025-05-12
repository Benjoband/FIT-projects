/**
 * @file fiber.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of fiber class
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "fiber.hpp"
#include "config.hpp"
#include "core.hpp"
#include <iostream>
#include <math.h>

Fiber::Fiber(sf::Vector2u corePos, sf::Vector2u coreSize, sf::Vector2u claddingTopPos,
             sf::Vector2u claddingBotPos, sf::Vector2u claddingTopSize,
             sf::Vector2u claddingBotSize, int type)
    : _core(corePos, coreSize), _type(type)
{
    _claddingStepIndexTop = sf::RectangleShape(sf::Vector2f(claddingTopSize.x, claddingTopSize.y));
    _claddingStepIndexTop.setPosition(sf::Vector2f(claddingTopPos.x, claddingTopPos.y));
    _claddingStepIndexTop.setFillColor(sf::Color::Black);

    _claddingStepIndexBot = sf::RectangleShape(sf::Vector2f(claddingBotSize.x, claddingBotSize.y));
    _claddingStepIndexBot.setPosition(sf::Vector2f(claddingBotPos.x, claddingBotPos.y));
    _claddingStepIndexBot.setFillColor(sf::Color::Black);

    _singleModeCladdingBot = sf::RectangleShape(sf::Vector2f(claddingBotSize.x, claddingBotSize.y));
}

Fiber::Fiber()
    : _claddingStepIndexTop(sf::RectangleShape(
          sf::Vector2f(config::CLADDING_WIDTH, config::CLADDING_STEP_INDEX_HEIGHT))),
      _claddingStepIndexBot(sf::RectangleShape(
          sf::Vector2f(config::CLADDING_WIDTH, config::CLADDING_STEP_INDEX_HEIGHT))),
      _singleModeCladdingTop(sf::RectangleShape(
          sf::Vector2f(config::CLADDING_WIDTH, config::CLADDING_SINGLE_MODE_HEIGHT))),
      _singleModeCladdingBot(sf::RectangleShape(
          sf::Vector2f(config::CLADDING_WIDTH, config::CLADDING_SINGLE_MODE_HEIGHT))),
      _claddingGradedIndexTop(sf::RectangleShape(
          sf::Vector2f(config::CLADDING_WIDTH, config::CLADDING_GRADED_INDEX_HEIGHT))),
      _claddingGradedIndexBot(sf::RectangleShape(
          sf::Vector2f(config::CLADDING_WIDTH, config::CLADDING_GRADED_INDEX_HEIGHT))),
      _core(), _type(0)
{
    _claddingStepIndexTop.setPosition(
        sf::Vector2f(config::CLADDING_X, config::CLADDING_STEP_TOP_Y));
    _claddingStepIndexTop.setFillColor(sf::Color::Black);
    _claddingStepIndexBot.setPosition(
        sf::Vector2f(config::CLADDING_X, config::CLADDING_STEP_BOT_Y));
    _claddingStepIndexBot.setFillColor(sf::Color::Black);

    _singleModeCladdingTop.setPosition(
        sf::Vector2f(config::CLADDING_X, config::CLADDING_SINGLE_TOP_Y));
    _singleModeCladdingTop.setFillColor(sf::Color::Black);
    _singleModeCladdingBot.setPosition(
        sf::Vector2f(config::CLADDING_X, config::CLADDING_SINGLE_BOT_Y));
    _singleModeCladdingBot.setFillColor(sf::Color::Black);

    _claddingGradedIndexTop.setPosition(
        sf::Vector2f(config::CLADDING_X, config::CLADDING_GRADED_TOP_Y));
    _claddingGradedIndexTop.setFillColor(sf::Color::Black);
    _claddingGradedIndexBot.setPosition(
        sf::Vector2f(config::CLADDING_X, config::CLADDING_GRADED_BOT_Y));
    _claddingGradedIndexBot.setFillColor(sf::Color::Black);

    int step = config::CORE_GRADED_INDEX_HEIGHT / config::GRADED_INDEX_N;
    sf::Color colors[config::GRADED_INDEX_N];
    for (int i = 0; i < config::GRADED_INDEX_N / 2; i++)
    {
        int color = (i * 255 / (config::GRADED_INDEX_N / 2)) + 40;
        colors[i] = sf::Color(color, color, color, 255);
        colors[config::GRADED_INDEX_N - i - 1] = sf::Color(color, color, color, 255);
    }

    for (int i = 0; i < 4; i++)
    {
        _stepindexCladding.push_back(
            sf::RectangleShape(sf::Vector2f(config::CLADDING_WIDTH, step)));
        _stepindexCladding[i].setPosition(
            sf::Vector2f(config::CLADDING_X, config::CLADDING_GRADED_TOP_Y +
                                                 config::CLADDING_GRADED_INDEX_HEIGHT + i * step));
        std::cout << "Y: "
                  << config::CLADDING_GRADED_TOP_Y + config::CLADDING_GRADED_INDEX_HEIGHT +
                         i * step + 16
                  << std::endl;
        _stepindexCladding[i].setFillColor(colors[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        _stepindexCladding.push_back(
            sf::RectangleShape(sf::Vector2f(config::CLADDING_WIDTH, step)));
        _stepindexCladding[i + 4].setPosition(sf::Vector2f(
            config::CLADDING_X,
            config::CLADDING_GRADED_TOP_Y + config::CLADDING_GRADED_INDEX_HEIGHT + (i + 4) * step));
        std::cout << "Y: "
                  << config::CLADDING_GRADED_TOP_Y + config::CLADDING_GRADED_INDEX_HEIGHT +
                         (i + 4) * step
                  << std::endl;
        _stepindexCladding[i + 4].setFillColor(colors[i + 4]);
    }
}

void Fiber::draw(sf::RenderWindow &window)
{
    _core.draw(window);

    if (_type == 0)
    {
        window.draw(_claddingStepIndexTop);
        window.draw(_claddingStepIndexBot);
    }
    else if (_type == 1)
    {
        window.draw(_claddingGradedIndexTop);
        window.draw(_claddingGradedIndexBot);
        for (auto &cladding : _stepindexCladding)
        {
            window.draw(cladding);
        }
    }
    else
    {
        window.draw(_singleModeCladdingTop);
        window.draw(_singleModeCladdingBot);
    }
}

void Fiber::setType(int type) { _type = type; }