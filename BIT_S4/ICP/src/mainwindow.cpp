/**
 * @file mainwindow.cpp
 * @author Samuel Čus (xcussa00)
 * @brief Main window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "mainwindow.h"
#include "./ui_aboutwindow.h"
#include "./ui_gamewindow.h"
#include "./ui_mainwindow.h"
#include "./ui_playwindow.h"
#include "aboutwindow.h"
#include "playwindow.h"
#include "replay.h"

#include "server.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	abwindow   = new AboutWindow(this);
	plwindow   = new PlayWindow(this);
	gamewindow = new GameWindow(this);

	//connect(quitpushButton, &QPushButton::clicked, [=](){close()});
	connect(ui->aboutpushButton, &QPushButton::clicked, this, &MainWindow::aboutbuttonclicked);
	connect(ui->playpushButton, &QPushButton::clicked, this, &MainWindow::playbuttonclicked);
	connect(ui->quitpushButton, &QPushButton::clicked, this, &MainWindow::quitbuttonclicked);
	connect(abwindow->ui->backpushButton, &QPushButton::clicked, this, &MainWindow::aboutbuttonclicked);

	connect(ui->replayPushButton, &QPushButton::clicked, [=] {
		auto replay = new Replay();
		connectTo("0.0.0.0");
		replay->setTcpClient(_client);
		replay->show();
		gamewindow->show();
		hide();
	});

	connect(plwindow->ui->hostButton, &QPushButton::clicked, [=]() {
		bool      ok{};
		const int port = QInputDialog::getInt(this, "Select port", "What port you want to host on?", 1234, 1, 65535, 1, &ok);

		QString mapFile = QFileDialog::getOpenFileName(this, "Select map", "./maps/");

		if (ok && !mapFile.isEmpty()) {
			startServer(port);
			_game->getMap()->loadMapFromFile(mapFile.toStdString());
			connectTo(QString("127.0.0.1:") + QString::number(port));
			gamewindow->show();
			plwindow->hide();
		}
	});

	connect(plwindow->ui->joinButton, &QPushButton::clicked, [=]() {
		bool          ok{};
		const QString target = QInputDialog::getText(this, "Connect to...", "Target to connect to: ", QLineEdit::Normal, "127.0.0.1:1234", &ok);
		connectTo(target);
		gamewindow->show();
		plwindow->hide();
	});


	connect(gamewindow, &GameWindow::keyPressed, [this](QKeyEvent* event) {
		qDebug() << "Key pressed received" << event->key();

		using D = ClientController::Direction;

		D direction;
		switch (event->key()) {
		case 'W':
			direction = D::UP;
			break;
		case 'A':
			direction = D::LEFT;
			break;
		case 'S':
			direction = D::DOWN;
			break;
		case 'D':
			direction = D::RIGHT;
			break;
		default:
			return;
		}

		_clientController->keyPressed(direction);
	});

	connect(gamewindow->ui->startButton, &QPushButton::clicked, [this]() {
		gamewindow->ui->startButton->setEnabled(false);
		_game->startGame();
	});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutbuttonclicked() {
	if (abwindow->isVisible()) {
		abwindow->hide();
		show();
	} else {
		hide();
		abwindow->show();
	}
}

void MainWindow::quitbuttonclicked() {
	close();
	QApplication::quit();
}

void MainWindow::playbuttonclicked() {
	if (plwindow->isVisible()) {
		plwindow->hide();
		show();
	} else {
		hide();
		plwindow->show();
	}
}

QGraphicsView* MainWindow::getGraphicsView() const {
	return gamewindow->ui->graphicsView;
}

void MainWindow::startServer(uint16_t port) {
	_server = std::make_shared<TcpServer>(port);
	_game   = std::make_shared<Game>(_server);
}

void MainWindow::stopServer() {
	_server.reset();
}

void MainWindow::connectTo(QString target) {
	_client           = std::make_shared<TcpClient>(target);
	_clientController = std::make_shared<ClientController>();
	_clientController->setView(getGraphicsView());
	_clientController->setClient(_client);
	_clientController->setUi(gamewindow->ui);
}
