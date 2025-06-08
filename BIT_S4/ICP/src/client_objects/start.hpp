/**
 * @file start.hpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Header file for start object painting
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef G_START_HPP
#define G_START_HPP

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>

namespace client {

/**
 * @brief Class for painting start object
 * 
 */
class Start : public QGraphicsItem {
public:
    Start();
    
    /**
     * @brief Draws rectangle for start object
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief Draws start object
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

#endif // G_START_HPP