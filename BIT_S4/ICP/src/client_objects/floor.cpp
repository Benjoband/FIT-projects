/**
 * @file floor.cpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief implementation of floor.h
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "floor.hpp"

#include <QPainter>

using namespace client;

Floor::Floor() {
    _pixmap = QPixmap("./graphics/floor.png");
}

QRectF Floor::boundingRect() const {
    // We draw "around" our position
    // Tile width = 20
    // Tile height = 20
    // So we start drawing in (-10,-10) -> our position is in the center of the image
    return QRectF(-10, -10, 20, 20);
}

void Floor::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->drawPixmap(-10, -10, 20, 20, _pixmap);
}