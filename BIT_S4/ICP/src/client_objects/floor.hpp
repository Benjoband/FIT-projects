/**
 * @file floor.hpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Header file for floor object painting
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef G_FLOOR_HPP
#define G_FLOOR_HPP

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>

namespace client {
/**
 * @brief Class for painting floor object
 * 
 */
class Floor : public QGraphicsItem {
public:
    Floor();

    /**
     * @brief Draws rectangle for floor object
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief Draws floor object
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

#endif // G_FLOOR_HPP