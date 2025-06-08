/**
 * @file gamewindow.h
 * @author Samuel Čus (xcussa00)
 * @brief Game window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit GameWindow(QWidget* parent = nullptr);
	~GameWindow();

	void keyPressEvent(QKeyEvent* event) override;

signals:
	void keyPressed(QKeyEvent* event);

public:
	Ui::GameWindow* ui;

private:
};

#endif // GAMEWINDOW_H
