/**
 * @file client_id.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of client_id.h
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "client_id.h"

#include <sstream>

using namespace communication;

constexpr char SEPARATOR{' '};

ClientIdMessage::ClientIdMessage() : Message{Type::ClientId} {
}

size_t ClientIdMessage::getClientId() const {
	return _id;
}

void ClientIdMessage::setClientId(size_t clientId) {
	_id = clientId;
}

std::string ClientIdMessage::serialize() const {
	std::string ret{Message::serialize()};
	ret += std::to_string(getClientId());
	ret += SEPARATOR;

	return ret;
}

void ClientIdMessage::deserialize(const std::string& message) {
	size_t id;

	std::istringstream ss{message};
	ss >> id;

	setClientId(id);
}
