/**
 * @file key.hpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Header file for key object painting
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef G_KEY_HPP
#define G_KEY_HPP

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>

namespace client {

/**
 * @brief Class for paining key object
 * 
 */
class Key : public QGraphicsItem {
public:
    Key();
    /**
     * @brief Draws rectangle for key object
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief Draws key object
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

#endif // G_KEY_HPP