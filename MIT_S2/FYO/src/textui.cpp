#include "textui.hpp"
#include <iostream>

TextUI::TextUI() : _font("font/hack-regular.ttf"), _controls(_font)
{
    _controls.setCharacterSize(18);
    _controls.setFillColor(sf::Color::Black);
    _controls.setPosition(sf::Vector2f(10, 10));
    _controls.setString("Controls:\n"
                        "  - Up | W:    Rotate up\n"
                        "  - Down | S:  Rotate down\n"
                        "  - Left | A:  Move left\n"
                        "  - Right | D: Move right\n"
                        "  - I:         Normal / infrared\n"
                        "  - O:         Switch core types\n"
                        "  - H:         Show/hide controls\n"
                        "  - Esc:       Exit the application");
}

void TextUI::draw(sf::RenderWindow &window) { window.draw(_controls); }