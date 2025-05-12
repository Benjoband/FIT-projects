#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <iostream>

#include "config.hpp"
#include "fiber.hpp"
#include "laser.hpp"
#include "ray.hpp"
#include "textui.hpp"

void handleEvents(sf::RenderWindow &window, Laser &laser, Ray &ray, Fiber &fiber, int &help,
                  int &type, int &infrared)
{
    while (const std::optional event = window.pollEvent())
    {
        // Window closed or escape key pressed: exit
        if (event->is<sf::Event::Closed>() ||
            (event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
        {
            std::cout << "Window closed" << std::endl;
            window.close();
        }
        // Rotate laser
        if ((event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) ||
            (event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W))
        {
            laser.updateRotation(-1, ray);
            std::cout << "Up" << std::endl;
            ray.reflection();
        }
        if ((event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) ||
            (event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S))
        {
            laser.updateRotation(1, ray);
            std::cout << "Down" << std::endl;
            ray.reflection();
        }

        // Move laser
        if ((event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) ||
            (event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A))
        {
            laser.updatePosition(-5);
            ray.updatePosition(-5);
            std::cout << "Left" << std::endl;
            ray.reflection();
        }
        if ((event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) ||
            (event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D))
        {
            laser.updatePosition(5);
            ray.updatePosition(5);
            std::cout << "Right" << std::endl;
            ray.reflection();
        }
        // Application states
        if ((event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::O))
        {
            if (type == 0)
                type = 1;
            else if (type == 1)
                type = 2;
            else
                type = 0;
            fiber.setType(type);
            ray.setType(type);
        }
        if ((event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::H))
        {
            if (help)
                help = 0;
            else
                help = 1;
        }
        if ((event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::I))
        {
            if (infrared)
            {
                infrared = 0;
                ray.setInfrared(0);
            }
            else
            {
                infrared = 1;
                ray.setInfrared(1);
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({config::SCREEN_WIDTH, config::SCREEN_HEIGHT}),
                            "Fiber Optics Simulation");
    window.setFramerateLimit(config::FPS);

    Laser laser;
    Ray ray;
    Fiber fiber;

    TextUI text;

    int help = 1;     // 0 - no help, 1 - help
    int type = 0;     // 0 - normal cladding, 1 - step index
    int infrared = 0; // 0 - no infrared, 1 - infrared

    while (window.isOpen())
    {
        handleEvents(window, laser, ray, fiber, help, type, infrared);

        window.clear(sf::Color::White);
        // Print controls
        if (help)
            text.draw(window);
        // Print core, cladding and fiber
        fiber.draw(window);
        // Print laser and ray
        laser.draw(window);
        ray.draw(window);

        window.display();
    }

    return 0;
}
