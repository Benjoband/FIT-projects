/**
 * @file object.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of object.h
 * @version 1.0
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "object.h"
#include <string>
#include <utility>

using namespace std;
using namespace server;

// Object class
// Constructors
Object::Object() = default;

Object::Object(int posX, int posY, int number) : _x{posX}, _y{posY}, _number{number} {
}

// Getters
int Object::getX() const {
	return _x;
}

int Object::getY() const {
	return _y;
}

int Object::getNumber() const {
	return _number;
}

std::shared_ptr<Map> Object::getMap() const {
	return _map;
}

std::shared_ptr<Game> Object::getGame() const {
	return _game;
}

// Setters
void Object::setX(int newX) {
	_x = newX;
}

void Object::setY(int newY) {
	_y = newY;
}

void Object::setNumber(int newNumber) {
	_number = newNumber;
}

void Object::setMap(std::shared_ptr<Map> map) {
	_map = std::move(map);
}

void Object::setGame(std::shared_ptr<Game> game) {
	_game = std::move(game);
}

string Object::toString() const {
	return {};
}
