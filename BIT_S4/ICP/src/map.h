/**
 * @file map.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for game's map. Representating only the map, not the game itself.
 * @version 1.0
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <QObject>

#include "server_objects/object.h"
#include "tiles.h"

/**
 * @brief Class for map representation, with all walls and floors and loading from file
 * 
 */
class Map : public QObject {
	Q_OBJECT
public:
	// Constructors
	Map();

	using Direction = server::Object::Direction;

	// Getters
	int                                  getSizeX() const;
	int                                  getSizeY() const;
	std::vector<std::vector<char>>       getTiles() const;

	// Setters
	void setSizeX(int columns);
	void setSizeY(int rows);
	void setTiles(std::vector<std::vector<char>> newTiles);

	/**
	 * @brief Gets the char tile from map on position posX, posY
	 * 
	 * @param posX 
	 * @param posY 
	 * @return char 
	 */
	char getTile(int posX, int posY);

	/**
     * @brief Loads the map from a file
     * 
     * @param filename 
     * @return int 
     */
	int loadMapFromFile(const std::string& filename);

	/**
     * @brief Puts map, players and their score and position etc. into string
     * 
     * @return string 
     */
	std::string toString();

signals:
	/**
	 * @brief Signal emitted when loading started
	 * 
	 * @param sizeX 
	 * @param sizeY 
	 */
	void loadingStarted(int sizeX, int sizeY);

	/**
	 * @brief Signal emitted when loading finished
	 * 
	 * @param x 
	 * @param y 
	 */
	void loadingWall(int x, int y);

	/**
	 * @brief Signal emitted when loading floor
	 * 
	 * @param x 
	 * @param y 
	 */
	void loadingFloor(int x, int y);

	/**
	 * @brief Signal emitted when loading key
	 * 
	 * @param x 
	 * @param y 
	 */
	void loadingKey(int x, int y);

	/**
	 * @brief Signal emitted when loading player
	 * 
	 * @param x 
	 * @param y 
	 */
	void loadingStart(int x, int y);

	/**
	 * @brief Signal emitted when loading target
	 * 
	 * @param x 
	 * @param y 
	 */
	void loadingTarget(int x, int y);

	/**
	 * @brief Signal emitted when loading ghost
	 * 
	 * @param x 
	 * @param y 
	 */
	void loadingGhost(int x, int y);

	/**
	 * @brief Signal emitted when loading player
	 * 
	 * @param x 
	 * @param y 
	 * @param id 
	 */
	void loadingPlayer(int x, int y, int id);

	/**
	 * @brief Signal emitted when loading finished
	 * 
	 */
	void loadingFinished();

private:
	/**
	 * @brief Reads the map size from file
	 * 
	 * @param file 
	 * @return std::pair<int, int> 
	 */
	static std::pair<int, int> readMapSizeFromFile(std::ifstream& file);
	
	/**
	 * @brief Loads the tiles from file and sends signals when loading objects
	 * 
	 * @param file 
	 */
	void                       loadTilesFromFile(std::ifstream& file);

private:
	int                            sizeX{0}, sizeY{0};
	std::vector<std::vector<char>> tiles;
};

#endif // MAP_H
