/**
 * @file player.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @author Patrik Olszar (xolsza00@stud.fit.vutbr.cz)
 * @brief Source file for player.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "player.h"
#include "../game.h"
#include "../map.h"
#include <iostream>

using namespace std;
using namespace server;

Player::Player(int x, int y, int objectId, int playerId) : Object{x, y, objectId}, playerId{playerId} {
}

// Getters
Player::Direction Player::getDirection() const {
	return direction;
}

int Player::getScore() const {
	return score;
}

int Player::getPlayerId() const {
	return playerId;
}

// Setters
void Player::setDirection(Direction newDirection) {
	direction = newDirection;
}

void Player::setScore(int newScore) {
	score = newScore;
}

void Player::worldTick() {
	int x{getX()};
	int y{getY()};

	switch (getDirection()) {
	case Direction::UP:
		y = y - 1;
		break;
	case Direction::RIGHT:
		x = x + 1;
		break;
	case Direction::DOWN:
		y = y + 1;
		break;
	case Direction::LEFT:
		x = x - 1;
		break;
	}

	auto map  = getMap();
	// auto game = getGame();

	if (x < 0 || x >= map->getSizeX() || y < 0 || y >= map->getSizeY()) {
		return;
	}
	auto tile = map->getTile(x, y);
	if (tile == WALL) {
		return;
	}
	setY(y);
	setX(x);
}

// Methods
std::string Player::toString() const {
	std::string result{"Player "};
	result += std::to_string(getX());
	result += " ";
	result += std::to_string(getY());
	result += " ";
	result += std::to_string(getNumber());
	result += " ";
	result += std::to_string(static_cast<int>(getDirection()));
	result += " ";
	result += std::to_string(getScore());
	result += "\n";
	return result;
}

char Player::mapRepresentation() const {
	return Tiles::PLAYER;
}

int Player::collision(vector<std::shared_ptr<server::Object>> objects) {
	for (auto object : objects) {
		if(object->mapRepresentation() == Tiles::GHOST){
			getGame()->endGame(1);
			return 1;
		} else if(object->mapRepresentation() == Tiles::KEY){
			dynamic_pointer_cast<server::Key>(object)->setTaken(true);
			setScore(getScore() + 100);
			return 0;
		} else if(object->mapRepresentation() == Tiles::TARGET){
			qDebug() << "Player collision with target\n";
			if(getGame()->getNumberOfKeys() > 0){
				if(getGame()->getNumberOfTakenKeys() >= 1){
					getGame()->endGame(0);
				}
				return 0; // TODO
			} else{
				getGame()->endGame(0);
				return 0;
			}
			return 0; // TODO
		} else if(object->mapRepresentation() == Tiles::PLAYER){
			continue;
		}
	}
	return 0;
}
