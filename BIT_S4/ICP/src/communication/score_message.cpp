/**
 * @file score_message.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of score_message.h
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "score_message.h"

#include <sstream>

using namespace communication;

constexpr char SEPARATOR{' '};

ScoreMessage::ScoreMessage() : Message{Type::Score} {
}

int ScoreMessage::getScore() const { 
    return _score; 
}

int ScoreMessage::getId() const { 
	return _id; 
}

void ScoreMessage::setScore(int score) { 
    _score = score; 
}

void ScoreMessage::setId(int id) { 
	_id = id; 
}

std::string communication::ScoreMessage::serialize() const {
    std::string ret{Message::serialize()};
	ret += std::to_string(getId());
	ret += SEPARATOR;
	ret += std::to_string(getScore());
	ret += SEPARATOR;

	return ret;
}

void communication::ScoreMessage::deserialize(const std::string& message) {
	int score,id;

	std::istringstream ss{message};
	ss>>id;
	setId(id);

	ss >> score;
	setScore(score);
}
