/**
 * @file map.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of map.h
 * @version 1.0
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "map.h"

#include <iostream>

using namespace std;

// maybe not needed
// Map::Map(int newX, int newY, int newNumOfGhosts, int newMode) : sizeX(newX), sizeY(newY), numOfGhosts(newNumOfGhosts), mode(newMode) {
//     tiles.resize(newY, std::vector<char>(newX, ' '));
// }

Map::Map() {
	connect(this, &Map::loadingStarted, [this](int size_x, int size_y) {
		setSizeX(size_x);
		setSizeY(size_y);
		tiles.clear();
		tiles.resize(size_x, std::vector<char>(size_y, Tiles::FLOOR));
	});

	connect(this, &Map::loadingWall, [this](int posX, int posY) { tiles.at(posY).at(posX) = Tiles::WALL; });
	//connect(this, &Map::loadingTarget, [this](int posX, int posY) { tiles.at(posY).at(posX) = Tiles::TARGET; });
}

// Getters
int Map::getSizeX() const {
	return sizeX;
}

int Map::getSizeY() const{
    return sizeY;
}

std::vector<std::vector<char>> Map::getTiles() const{
    return tiles;
}

// Setters
void Map::setSizeX(int columns){
    sizeX = columns;
}

void Map::setSizeY(int rows){
    sizeY = rows;
}

void Map::setTiles(std::vector<std::vector<char>> newTiles){
    tiles = std::move(newTiles);
}

// Functions
char Map::getTile(int column, int row) {
    return tiles.at(row).at(column);
}

std::pair<int, int> Map::readMapSizeFromFile(ifstream& file) {
	string line;
	getline(file, line);
	int    count{0};
	int    sizeX{0};
	int    sizeY{0};
	string num;
	for (const auto& character : line) {
		if (isdigit(character)) {
			num += character;
		} else if (count == 0) {
			sizeX = stoi(num);
			num   = "";
			count = 1;
		}
	}
	sizeY = stoi(num);
	return {sizeX, sizeY};
}

void Map::loadTilesFromFile(ifstream& file) {
	string line;
	int startCount = 0;
	for (int y = 0; y < sizeY; y++) {
		if (!getline(file, line)) {
			return;
		}
		for (int x = 0; x < sizeX; x++) {
			if (line[x] == '\n' || line[x] == '\r' || line[x] == ' ') {
				continue;
			}
			switch (line[x]) {
			case Tiles::FLOOR:
				loadingFloor(x, y);
				break;
			case Tiles::GHOST:
				loadingGhost(x, y);
				break;
			case Tiles::KEY:
				loadingKey(x, y);
				break;
			case Tiles::START:
				loadingStart(x, y);
				break;
			case Tiles::TARGET:
				loadingTarget(x, y);
				break;
			case Tiles::WALL:
				loadingWall(x, y);
				break;
			}
		}
	}
}

int Map::loadMapFromFile(const string& filename) {
	ifstream file(filename);
	if (file.is_open()) {
		auto [sizeX, sizeY] = readMapSizeFromFile(file);
		emit loadingStarted(sizeX, sizeY);
		loadTilesFromFile(file);
		emit loadingFinished();
	} else {
		return -1;
	}
	file.close();
	return 0;
}

string Map::toString() {
	string str = "";
	str += "X: " + to_string(getSizeX()) + "\n";
	str += "Y: " + to_string(getSizeY()) + "\n";
	for (int y = 0; y < getSizeY(); y++) {
		for (int x = 0; x < getSizeX(); x++) {
			str += getTile(x, y);
		}
		str += "\n";
	}
	return str;
}
