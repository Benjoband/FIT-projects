/**
 * @file main.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @author Patrik Olszar (xolsza00@stud.fit.vutbr.cz)
 * @author Samuel Čus (xcussa00@stud.fit.vutbr.cz)
 * @brief Main file of game.
 * @version 0.1
 * @date 2023-05-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "client.h"
#include "client_controller.h"
#include "game.h"
#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow   w;
	w.show();
	return a.exec();
}
