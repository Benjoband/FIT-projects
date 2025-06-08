/**
 * @file game.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @author Patrik Olszar (xolsza00@stud.fit.vutbr.cz)
 * @brief Implementation of game.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "game.h"
#include <fstream>
#include <string>

#include <iostream>

using namespace std;
using namespace server;

// constructors
Game::Game(std::shared_ptr<TcpServer> server) : _timer{new QTimer(this)}, _server{server} {
	if (!std::filesystem::exists("./logs/")) {
		std::filesystem::create_directory("./logs/");
	}

	_logFile.open("./logs/" + dateUtils::getCurrentDateTimeString() + ".txt");
	if(!_logFile.is_open()) {
		qDebug("Failed to open log file");
		qDebug(dateUtils::getCurrentDateTimeString().c_str());
		exit(1);
	}
	_map = std::make_shared<Map>();

	connect(_map.get(), &Map::loadingStarted, [this](int size_x, int size_y) {
		_objects.clear();
		_players.clear();
		_ghosts.clear();
		_keys.clear();
	});

	connect(_map.get(), &Map::loadingGhost, [this](int posX, int posY) {
		auto ghost = std::make_shared<Ghost>(posX, posY, generateId());
		addGhost(ghost);
	});

	connect(_map.get(), &Map::loadingKey, [this](int posX, int posY) {
		auto key = std::make_shared<Key>(posX, posY, generateId());
		addKey(key);
	});

	connect(_map.get(), &Map::loadingStart, [this](int posX, int posY) {
		auto start = std::make_shared<Start>(posX, posY, generateId());
		addStart(start);
	});

	connect(_map.get(), &Map::loadingTarget, [this](int posX, int posY) {
		auto target = std::make_shared<Target>(posX, posY);
		addTarget(target);
	});

	connect(server.get(), &TcpServer::direction_message_received, [this](Direction direction, size_t id) {
		qDebug() << "SERVER received: " << static_cast<int>(direction) << " " << id;
		for(auto player : _players)
		{
			if(player->getPlayerId() == id)
			{
				player->setDirection(direction);
			}
		}
	});

	connect(_server.get(), &TcpServer::messageSent, [this](std::string message) -> void {
		_logFile << message << endl;
	});

	// Tick tock
	_timer->setSingleShot(false);
	_timer->setInterval(500);
	connect(_timer, &QTimer::timeout, [this] { gameTick(); });

	// server
	_server->setIdGenerator([=]() { return generatePlayerId(); });
}

// Getters
std::shared_ptr<Map> Game::getMap() const {
	return _map;
}

// Functions
int Game::gameTick() {
	qDebug() << "keys:" << getNumberOfTakenKeys() << "/" << getNumberOfKeys();
	for (const auto& object : _objects) {
		object->worldTick();
		auto collisions = getObjectsAt(object->getX(), object->getY(), object);
		if(!collisions.empty())
		{
			if(object->collision(collisions) == 1)
			{
				return 1;
			}
		}
	}

	{
		communication::MapMessage mapUpdate;
		auto                      tiles = getMap()->getTiles();
		for (int y{0}; y < tiles.size(); ++y) {
			for (int x{0}; x < tiles[0].size(); ++x) {
				auto obj = std::find_if(_objects.begin(), _objects.end(), [x, y](auto obj) { return obj->getX() == x && obj->getY() == y; });

				if (obj != std::end(_objects) && (*obj)->mapRepresentation() != 0) {
					tiles.at(y).at(x) = (*obj)->mapRepresentation();
				}
			}
		}
		for(auto player : _players)
		{
			tiles.at(player->getY()).at(player->getX()) = player->mapRepresentation();
		}
		mapUpdate.setMapData(tiles);
		_server->send_message(&mapUpdate);
	}

	{
		communication::KeysMessage keysUpdate;
		keysUpdate.setCollected(getNumberOfTakenKeys());
		keysUpdate.setNumKeysToWin(getNumberOfKeys());
		_server->send_message(&keysUpdate);
	}

	for (auto player : _players) {
		// TODO: compute score for each player separately
		communication::ScoreMessage scoreMessage;
		scoreMessage.setScore(player->getScore());
		scoreMessage.setId(player->getPlayerId());
		getServer()->send_message(&scoreMessage);
	}

	return 0;
}

void Game::addObject(std::shared_ptr<server::Object> map_object) {
    map_object->setMap(getMap());
	map_object->setGame(shared_from_this());
	_objects.emplace_back(std::move(map_object));
}

void Game::addPlayer(std::shared_ptr<server::Player> player) {
	_players.emplace_back(player);
	addObject(player);
}

void Game::addGhost(std::shared_ptr<server::Ghost> ghost) {
	_ghosts.emplace_back(ghost);
	addObject(ghost);
}

void Game::addStart(std::shared_ptr<server::Start> start) {
	_start = start;
}

void Game::addKey(std::shared_ptr<server::Key> key) {
	_keys.emplace_back(key);
	addObject(key);
}

void Game::addTarget(std::shared_ptr<server::Target> target) {
	addObject(target);
}

int Game::getNumberOfTakenKeys() const {
	return std::count_if(_keys.begin(), _keys.end(), [](auto k) { return k->isTaken(); });
}

int Game::getNumberOfKeys() const {
	return _keys.size();
}

int Game::logMap() {
	_logFile << _map->getSizeX() << " " << _map->getSizeY() << endl;

	for (int y{0}; y < _map->getSizeY(); ++y) {
		for (int x{0}; x < _map->getSizeX(); ++x) {
			auto obj = std::find_if(_objects.begin(), _objects.end(), [x, y](auto obj) { return obj->getX() == x && obj->getY() == y; });

			if (obj != std::end(_objects) && (*obj)->mapRepresentation() != 0) {
				_logFile << (*obj)->mapRepresentation();
			} else {
				_logFile << _map->getTile(x, y);
			}
		}
		_logFile << std::endl;
	}
	for(auto players : _players)
	{
		_logFile << players->getNumber() << players->getX() << " " << players->getY() << players->getScore() << endl;
	}
	_logFile << getNumberOfTakenKeys() << " " << getNumberOfTakenKeys() << endl;
	return 0;
}

std::shared_ptr<TcpServer> Game::getServer() {
	return _server;
}

size_t Game::generateId() {
	return ++_id;
}

size_t Game::generatePlayerId() {
	return _numOfPlayers++;
}

int Game::startGame() {
	qDebug() << "Starting game";
	if (!_start) {
		qDebug() << "Game does not contains START tile";
	}

	for (int i = 0; i < _numOfPlayers; i++) {
		addPlayer(std::make_shared<Player>(_start->getX(), _start->getY(), generateId(), i));
	}
	_timer->start();

	return 0;
}

int Game::endGame(int state){
	communication::EndingMessage end;
	switch (state){
	case 0:
		// win TODO: send to client
		end.setEnding(static_cast<communication::EndingMessage::Ending>(1));
		_server->send_message(&end);
		break;
	case 1:
		// lose TODO: send to client
		end.setEnding(static_cast<communication::EndingMessage::Ending>(2));
		_server->send_message(&end);
		break;
	default:
		break;
	}
	_timer->stop();
	_logFile.close();
	return 0;
}

std::vector<std::shared_ptr<server::Object>> Game::getObjectsAt(int x, int y, std::shared_ptr<server::Object> o) const {
	std::vector<std::shared_ptr<server::Object>> objects;
	for (const auto& object : _objects) {
		if (object == o) // ignore object that called this function
			continue;
		if (object->getX() == x && object->getY() == y) {
			objects.emplace_back(object);
		}
	}
	return objects;
}
