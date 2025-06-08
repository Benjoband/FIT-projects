/**
 * @file mainwindow.h
 * @author Samuel Čus (xcussa00)
 * @brief Main window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aboutwindow.h"
#include "gamewindow.h"
#include "playwindow.h"
#include <QMainWindow>

#include "client.h"
#include "client_controller.h"
#include "game.h"
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;
	void aboutbuttonclicked();
	void quitbuttonclicked();
	void playbuttonclicked();

	QGraphicsView* getGraphicsView() const;

public slots:
	void startServer(uint16_t port);
	void stopServer();

	void connectTo(QString target);

private:
	Ui::MainWindow* ui{nullptr};
	AboutWindow*    abwindow{};
	PlayWindow*     plwindow{};
	GameWindow*     gamewindow{};

	std::shared_ptr<TcpClient>        _client;
	std::shared_ptr<ClientController> _clientController;
	std::shared_ptr<TcpServer>        _server;
	std::shared_ptr<Game>             _game;
};
#endif // MAINWINDOW_H
