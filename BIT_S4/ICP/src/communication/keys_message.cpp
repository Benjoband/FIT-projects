/**
 * @file keys_message.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of keys_message.h
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "keys_message.h"

#include <sstream>

using namespace communication;

constexpr char SEPARATOR{' '};

KeysMessage::KeysMessage() : Message{Type::Keys} {
}

int KeysMessage::getCollected() const {
    return _collected;
}

int KeysMessage::getNumKeysToWin() const {
    return _numKeysToWin;
}

void KeysMessage::setCollected(int collected) {
    _collected = collected;
}

void KeysMessage::setNumKeysToWin(int numKeysToWin) {
    _numKeysToWin = numKeysToWin;
}

std::string communication::KeysMessage::serialize() const {
    std::string ret{Message::serialize()};
    ret += std::to_string(getCollected());
    ret += SEPARATOR;
    ret += std::to_string(getNumKeysToWin());
    ret += SEPARATOR;

    return ret;
}

void communication::KeysMessage::deserialize(const std::string& message) {
    int collected;
    int numKeysToWin;

    std::istringstream ss{message};
    ss >> collected >> numKeysToWin;

    setCollected(collected);
    setNumKeysToWin(numKeysToWin);
}
