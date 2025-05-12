#ifndef TEXTUI_HPP
#define TEXTUI_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TextUI
{
    public:
        TextUI();
        void draw(sf::RenderWindow &window);

    private:
        sf::Font _font;
        sf::Text _controls;
};

#endif