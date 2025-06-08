/**
 * @file gamewindow.cpp
 * @author Samuel Čus (xcussa00)
 * @brief Game window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "client.h"

#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) :
      QMainWindow(parent),
      ui(new Ui::GameWindow)
{
	ui->setupUi(this);
}

GameWindow::~GameWindow()
{
	delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
	emit keyPressed(event);
}
