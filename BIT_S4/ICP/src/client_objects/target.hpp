/**
 * @file target.hpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Header file for target object painting
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef G_TARGET_HPP
#define G_TARGET_HPP

#include <QGraphicsItem>

namespace client {

/**
 * @brief Class for painting target object
 * 
 */
class Target : public QGraphicsItem {
public:
    Target();

    /**
     * @brief Draws rectangle for target object
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief Draws target object
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

#endif // G_TARGET_HPP