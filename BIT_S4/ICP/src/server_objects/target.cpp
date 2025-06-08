/**
 * @file target.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of target object
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "target.h"
#include "../tiles.h"

using namespace server;

Target::Target() : Object{0, 0, 0} {
}

Target::Target(int x, int y) : Object{x, y, 0} {
}

void Target::worldTick() {
}

std::string Target::toString() const {
    return "Target " + std::to_string(getX()) + " " + std::to_string(getY());
}

char Target::mapRepresentation() const {
    return Tiles::TARGET;
}

int Target::collision(std::vector<std::shared_ptr<Object>> objects) {
    return 0;
}
