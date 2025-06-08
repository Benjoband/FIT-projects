/**
 * @file client_controller.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of client_controller.h
 * @version 1.0
 * @date 2023-05-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "client_controller.h"
#include "tiles.h"

#include "client_objects/wall.hpp"
#include "client_objects/floor.hpp"
#include "client_objects/ghost.hpp"
#include "client_objects/pacman.hpp"
#include "client_objects/key.hpp"
#include "client_objects/start.hpp"
#include "client_objects/target.hpp"

#include <QEvent>
#include <QGraphicsView>

using namespace client;

constexpr double TILE_WIDTH{20};
constexpr double TILE_HEIGHT{20};

ClientController::ClientController(QObject* parent) : QObject{parent}, _scene{new QGraphicsScene(this)} {
}

void ClientController::setView(QGraphicsView* view) {
	_view = view;
	_view->setScene(_scene);

	_view->installEventFilter(this);
}

void ClientController::setUi(Ui::GameWindow* ui) {
	_ui = ui;
}

void ClientController::setClient(std::shared_ptr<TcpClient> client) {
	_client = client;

	connect(_client.get(), &TcpClient::map_message_received, [this](communication::MapMessage map) { setMapData(map.getMapData()); });

	connect(_client.get(), &TcpClient::score_message_received, [this](communication::ScoreMessage score) {
		setScore(score.getScore(), score.getId());
	});

	connect(_client.get(), &TcpClient::keys_message_received, [this](communication::KeysMessage keys) {
		setKeys(keys.getCollected(), keys.getNumKeysToWin());
	});

	connect(_client.get(), &TcpClient::ending_message_received, [this](communication::EndingMessage ending) {
		setEnding(ending.getEnding());
	});
}

void ClientController::setScore(int score, int id) {
	_ui->label->setText("Score: " + QString::number(score));
}

void ClientController::setKeys(int collected, int total) {
	_ui->label_3->setText("Keys: " + QString::number(collected) + "/" + QString::number(total));
}

void ClientController::setEnding(Ending state){
	qDebug() << "Ending ";
}

void ClientController::setMapData(std::vector<std::vector<char> > mapData) {
	_scene->clear();

	size_t height{mapData.size()};
	size_t width{height > 0 ? mapData[0].size() : 0};

	if (height == 0) {
		width  = 1;
		height = 1;
	}

	_view->setSceneRect({-TILE_WIDTH / 2, -TILE_HEIGHT / 2, width * TILE_WIDTH, height * TILE_HEIGHT});
	_view->fitInView(_view->sceneRect(), Qt::KeepAspectRatio);

	qDebug() << "creating Map view";

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			switch (mapData.at(y).at(x)) {
				case Tiles::WALL: {
					auto wall = new Wall();
					wall->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
					_scene->addItem(wall);
				} break;
				case Tiles::FLOOR: {
					auto floor = new Floor();
					floor->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
					_scene->addItem(floor);
				} break;
				case Tiles::GHOST: {
					auto ghost = new Ghost();
					ghost->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
					_scene->addItem(ghost);
				} break;
				case Tiles::KEY: {
					auto key = new Key();
					key->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
					_scene->addItem(key);
				} break;
				case Tiles::START: {
					auto start = new Start();
					start->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
					_scene->addItem(start);
				} break;
				case Tiles::TARGET: {
					auto target = new Target();
					target->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
					_scene->addItem(target);
				} break;
				case Tiles::PLAYER: {
					auto pacman = new Pacman();
					pacman->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
					_scene->addItem(pacman);
				} break;
				default:
					break;
			}
		}
	}
}

void ClientController::keyPressed(Direction d) {
	communication::DirectionMessage msg;
	
    msg.setDirection(d);
	msg.setId(_client->get_id());
	_client->send_message(&msg);
}

bool ClientController::eventFilter(QObject* object, QEvent* event) {
	if (object == _view && (event->type() == QEvent::Resize || event->type() == QEvent::Show)) {
		_view->fitInView(_view->sceneRect(), Qt::KeepAspectRatio);
	}
	return QObject::eventFilter(object, event);
}
