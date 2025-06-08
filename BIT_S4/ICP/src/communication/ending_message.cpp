/**
 * @file ending_message.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of ending_message.h
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ending_message.h"

#include <sstream>

using namespace communication;

constexpr char SEPARATOR{' '};

EndingMessage::EndingMessage() : Message{Type::Ending} {
}

EndingMessage::Ending EndingMessage::getEnding() const {
    return _ending;
}

void EndingMessage::setEnding(Ending ending) {
    _ending = ending;
}

std::string communication::EndingMessage::serialize() const {
    std::string ret{Message::serialize()};
    ret += std::to_string(static_cast<int>(getEnding()));
    ret += SEPARATOR;

    return ret;
}

void communication::EndingMessage::deserialize(const std::string& message) {
    int ending;

    std::istringstream ss{message};
    ss >> ending;

    setEnding(static_cast<Ending>(ending));
}