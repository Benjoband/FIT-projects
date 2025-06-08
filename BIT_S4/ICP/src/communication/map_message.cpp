/**
 * @file map_message.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of map_message.h
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "map_message.h"

#include <sstream>

using namespace communication;

constexpr char SEPARATOR{' '};

MapMessage::MapMessage() : Message{Type::Map} {
}

std::vector<std::vector<char>> MapMessage::getMapData() const {
	return _mapData;
}

void MapMessage::setMapData(const std::vector<std::vector<char>>& mapData) {
	_mapData = mapData;
}

void MapMessage::clearMapData() {
	_mapData.clear();
}

int MapMessage::getHeight() const {
	return _mapData.size();
}

int MapMessage::getWidth() const {
	return _mapData.size() ? _mapData[0].size() : 0;
}

std::string communication::MapMessage::serialize() const {
	const int height = getHeight();
	const int width  = getWidth();

	std::string ret{Message::serialize()};
	ret += std::to_string(height);
	ret += SEPARATOR;
	ret += std::to_string(width);
	ret += SEPARATOR;
	ret.reserve(height * width * 2);

	for (const auto& line : getMapData()) {
		for (const auto& cell : line) {
            ret.push_back(cell);
		}
		ret += SEPARATOR;
	}

	return ret;
}

void communication::MapMessage::deserialize(const std::string& message) {
	clearMapData();
	std::string line;

	int dummy{};

	std::istringstream ss{message};
	ss >> dummy >> dummy;

	while (ss.peek() == SEPARATOR) {
		ss.ignore();
	}

	std::vector<std::vector<char>> mapData;
	while (std::getline(ss, line, SEPARATOR)) {
		std::vector<char> lineData;
		for (const auto& cell : line) {
			lineData.push_back(cell);
		}
		mapData.push_back(lineData);
	}
	setMapData(mapData);
}
