/**
 * @file pacman.hpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Header file for pacman object painting
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef G_PACMAN_HPP
#define G_PACMAN_HPP

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>

namespace client {

/**
 * @brief Class for painting pacman object
 * 
 */
class Pacman : public QGraphicsItem {
public:
    Pacman();

    void setDirection(int direction);
    void setId(int id);

    int  getDirection();
    int  getId();

    /**
     * @brief Draws rectangle for pacman object
     * 
     * @return QRectF 
     */
    QRectF boundingRect() const override;

    /**
     * @brief Draws pacman object
     * 
     * @param painter 
     * @param option 
     * @param widget 
     */
    void   paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    int _direction{0};
    int _id{0};
    QPixmap _pixmap;
};

} // namespace client

#endif // G_PACMAN_HPP