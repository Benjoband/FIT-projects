/**
 * @file direction_message.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of direction_message.h
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "direction_message.h"

#include <sstream>

using namespace communication;

constexpr char SEPARATOR{' '};

DirectionMessage::DirectionMessage() : Message{Type::Direction} {
}

DirectionMessage::Direction DirectionMessage::getDirection() const {
	return _direction;
}

int DirectionMessage::getId() const {
	return id;
}

void DirectionMessage::setDirection(Direction direction) {
	_direction = direction;
}

void DirectionMessage::setId(int ID) {
	id = ID;
}

std::string communication::DirectionMessage::serialize() const {
    std::string ret{Message::serialize()};
    ret += std::to_string(static_cast<int>(getDirection()));
    ret += SEPARATOR;
    ret += std::to_string(getId());
    ret += SEPARATOR;

    return ret;
}

void communication::DirectionMessage::deserialize(const std::string& message) {
    int direction, id;

    std::istringstream ss{message};
    ss >> direction;
    setDirection(static_cast<Direction>(direction));

    ss >> id;
    setId(id);
}
