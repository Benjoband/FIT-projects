/**
 * @file key.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of key.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "key.h"
#include "../tiles.h"

using namespace server;

Key::Key(int posX, int posY, int number) : Object{posX, posY, number} {
}

void Key::worldTick() {
}

std::string Key::toString() const {
	return "Key " + std::to_string(getX()) + " " + std::to_string(getY());
}

char Key::mapRepresentation() const {
	return _taken ? 0 : Tiles::KEY;
}

bool Key::isTaken() const {
	return _taken;
}

void Key::setTaken(bool taken) {
	_taken = taken;
}

int Key::collision(std::vector<std::shared_ptr<server::Object>>) {
	return 0;
}