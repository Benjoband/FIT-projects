/**
 * @file ghost.hpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Header file for ghost object painting
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef G_GHOST_HPP
#define G_GHOST_HPP

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>

namespace client {

/**
 * @brief Class for painting ghost object
 * 
 */
class Ghost : public QGraphicsItem {
public:
    Ghost();

    /**
     * @brief Draws rectangle for ghost object
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief Draws ghost object
     * 
     * @param painter 
     * @param option 
     * @param widget 
     */
    void   paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPixmap _pixmap;
};

} // namespace client

#endif // G_GHOST_HPP