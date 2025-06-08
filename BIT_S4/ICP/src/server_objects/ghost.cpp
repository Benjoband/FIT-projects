/**
 * @file ghost.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @author Patrik Olszar (xolsza00@stud.fit.vutbr.cz)
 * @brief Implementation of ghost.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "object.h"
#include "ghost.h"
#include "../map.h"
#include "../game.h"
#include <iostream>

using namespace std;
using namespace server;

Ghost::Ghost() = default;

Ghost::Ghost(int posX, int posY, int number) : Object{posX, posY, number} {
}

Object::Direction Ghost::getDirection() const {
	return _direction;
}

void Ghost::setDirection(Direction dir) {
	_direction = dir;
}

void Ghost::worldTick() {
	// TODO: here you do A* and shit
	// You can get map information like this:
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

	auto map = getMap();

	if (x < 0 || x >= map->getSizeX() || y < 0 || y >= map->getSizeY()) {
		setDirection(getNewDirection(getX(),getY()));
		return;
	}
	if(map->getTile(x, y) == WALL){
		setDirection(getNewDirection(getX(),getY()));
		return;
	}
	setX(x);
	setY(y);
}

Object::Direction Ghost::getNewDirection(int x,int y) {
    vector<Object::Direction> newDirections = {};
	auto map = getMap();

	try{
		if (map->getTile(x+1,y) != WALL && x+1 < map->getSizeX()) {
			newDirections.push_back(Direction::RIGHT);
		}
	} catch (std::out_of_range& oor) {
		qDebug() << "Invalid message " << oor.what();
	}
	try{
		if (map->getTile(x-1,y) != WALL && x-1 >= 0) {
			newDirections.push_back(Direction::LEFT);
		}
	} catch (std::out_of_range& oor) {
		qDebug() << "Invalid message " << oor.what();
	}	
	try{
		if (map->getTile(x,y+1) != WALL && y+1 < map->getSizeY()) {
			newDirections.push_back(Direction::DOWN);
		}
	} catch (std::out_of_range& oor) {
		qDebug() << "Invalid message " << oor.what();
	}
	try{
		if (map->getTile(x,y-1) != WALL && y-1 >= 0) {
			newDirections.push_back(Direction::UP);
		}
	} catch (std::out_of_range& oor) {
		qDebug() << "Invalid message " << oor.what();
	}

	if (newDirections.size() == 0) {
		return getDirection();
	}

	int randomIndex = rand() % newDirections.size();
	return newDirections[randomIndex];
}

string Ghost::toString() const {
	std::string result;
	result += to_string(getX());
	result += " ";
	result += to_string(getY());
	result += " ";
	result += to_string(getNumber());
	return result;
}

char Ghost::mapRepresentation() const {
	return Tiles::GHOST;
}

int Ghost::collision(std::vector<std::shared_ptr<server::Object>> objects) {
	for(auto object : objects){
		if(object->mapRepresentation() == Tiles::PLAYER){
			getGame()->endGame(1);
		} else if(object->mapRepresentation() == Tiles::GHOST){
			continue;
		}
	}
	return 0;
}
