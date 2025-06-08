/**
 * @file pacman.cpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Implementation of pacman.hpp
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "pacman.hpp"

#include <QPainter>

using namespace client;

Pacman::Pacman() {
    _pixmap = QPixmap("./graphics/pacmanright.png");
}

QRectF Pacman::boundingRect() const {
    // We draw "around" our position
    // Tile width = 20
    // Tile height = 20
    // So we start drawing in (-10,-10) -> our position is in the center of the image
    return QRectF(-10, -10, 20, 20);
}

void Pacman::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if(_direction == 0)
        _pixmap = QPixmap("./graphics/pacmanup.png");
    else if(_direction == 1)
        _pixmap = QPixmap("./graphics/pacmanright.png");
    else if(_direction == 2)
        _pixmap = QPixmap("./graphics/pacmandown.png");
    else if(_direction == 3)
        _pixmap = QPixmap("./graphics/pacmanleft.png");
    painter->drawPixmap(-10, -10, 20, 20, _pixmap);
}

int Pacman::getDirection() {
    return _direction;
}

void Pacman::setDirection(int direction) {
    _direction = direction;
}

void Pacman::setId(int id) {
    _id = id;
}

int Pacman::getId() {
    return _id;
}

