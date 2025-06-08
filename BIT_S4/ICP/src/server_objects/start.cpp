/**
 * @file start.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Source file for start.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "start.h"
#include "../tiles.h"

using namespace server;

Start::Start(int x, int y, int id) : Object{x, y, id} {
}

void Start::worldTick() {
}

std::string Start::toString() const {
	return "Start " + std::to_string(getX()) + " " + std::to_string(getY());
}

char Start::mapRepresentation() const {
	return Tiles::START;
}

int Start::collision(std::vector<std::shared_ptr<server::Object>>) {
	return 0;
}
