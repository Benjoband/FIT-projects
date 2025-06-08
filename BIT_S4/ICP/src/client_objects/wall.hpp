/**
 * @file wall.hpp
 * @author Alexej Beňuš (xbenus01@fit.vutbr.cz)
 * @brief Header file for wall object painting
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef G_WALL_HPP
#define G_WALL_HPP

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>

namespace client {

/**
 * @brief Class for painting wall object
 * 
 */
class Wall : public QGraphicsItem {
public:
	Wall();

	/**
	 * @brief Draws rectangle for wall object
	 * 
	 * @return QRectF 
	 */
	QRectF boundingRect() const override;

	/**
	 * @brief Draws wall object
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

#endif // G_WALL_HPP
