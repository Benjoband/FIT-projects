/**
 * @file game.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of game
 * @version 0.1
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GAME_H
#define GAME_H

#include "dateutils.h"
#include "map.h"
#include "server.h"
#include <fstream>
#include <string>
#include <QObject>
#include <QTimer>

#include "server_objects/object.h"
#include "server_objects/ghost.h"
#include "server_objects/key.h"
#include "server_objects/player.h"
#include "server_objects/start.h"
#include "server_objects/target.h"

#include "communication/direction_message.h"

/**
 * @brief Game class for game logic, objects and map
 * 
 */
class Game : public QObject, public std::enable_shared_from_this<Game> {
	Q_OBJECT
public:
	using Direction = server::Object::Direction;

	// Constructors
	Game(std::shared_ptr<TcpServer>);

	// Getters
	std::shared_ptr<Map> getMap() const;
	std::ofstream&       getLogFile();
	std::vector<std::shared_ptr<server::Object>>& getObjects();
	int                                           getNumOfPlayers() const;

	// Setters
	void setLogFile(std::ofstream newLogFile);
	void setNumOfPlayers(int newNumOfPlayers);

	// Methods
	/**
	 * @brief Logs map to log file
	 * 
	 * @return int 
	 */
	int logMap();

	/**
	 * @brief Starts game, initializes all objects etc.
	 * 
	 * @return int 
	 */
	int startGame();

	/**
	 * @brief If player loses or wins, ends game
	 * 
	 * @param state 
	 * @return int 
	 */
	int endGame(int state);

	/**
	 * @brief Every game tick means one move in game. Moves all objects in game. Logs map into file
	 * 
	 * @return int 
	 */
	int gameTick();

	/**
	 * @brief Get the Objects At object, for knowing if there is a collision
	 * 
	 * @param x 
	 * @param y 
	 * @param o 
	 * @return std::vector<std::shared_ptr<server::Object>> 
	 */
	std::vector<std::shared_ptr<server::Object>> getObjectsAt(int x, int y, std::shared_ptr<server::Object> o) const;

	// Functions for adding objects to game

	/**
	 * @brief Adds the given map object to the object list.
	 *
	 * @param map_object The map object to add.
	 *
	 * This function adds the given map object to the object list.
	 */
	void addObject(std::shared_ptr<server::Object> map_object);


	/**
	 * @brief Adds a player to the game.
	 *
	 * @param player A shared pointer to a Player object.
	 */
	void addPlayer(std::shared_ptr<server::Player> player);

	/**
	 * @brief Adds a ghost to the game.
	 *
	 * @param ghost A shared pointer to a Ghost object.
	 */
	void addGhost(std::shared_ptr<server::Ghost> ghost);

	/**
	 * @brief Adds a key to the game.
	 *
	 * @param key A shared pointer to a Key object.
	 */
	void addKey(std::shared_ptr<server::Key> key);

	/**
	 * @brief Adds a start point to the game.
	 *
	 * @param start A shared pointer to a Start object.
	 */
	void addStart(std::shared_ptr<server::Start> start);

	/**
	 * @brief Adds a target to the game.
	 *
	 * @param target A shared pointer to a Target object.
	 */
	void addTarget(std::shared_ptr<server::Target> target);

	/**
	 * @brief Returns the number of taken keys
	 * @return An integer value representing the number of taken keys
	 */
	int getNumberOfTakenKeys() const;

	/**
	 * @brief Returns the total number of keys
	 * @return An integer value representing the total number of keys
	 */
	int getNumberOfKeys() const;

	/**
	 * @brief Returns a shared pointer to a TcpServer object.
	 *
	 * @return A shared pointer to a TcpServer object.
	 */
	std::shared_ptr<TcpServer> getServer();

	/**
	 * @brief Generates and returns a unique ID.
	 *
	 * @return A unique ID.
	 */
	size_t generateId();

	/**
	 * @brief Generates and returns a unique player ID.
	 *
	 * @return A unique player ID.
	 */
	size_t generatePlayerId();

signals:
	/**
	 * @brief Notifies the game that an update has occurred.
	 *
	 * This function should be called whenever a change is made to the game state that other parts
	 * of the game (such as the UI) may need to be aware of. It does not take any parameters or
	 * return any values.
	 *
	 */
	void gameUpdated(); // server can connect here to send updates

private:
	std::ofstream _logFile;
	QTimer*       _timer;

	std::shared_ptr<Map>                         _map;
	std::vector<std::shared_ptr<server::Object>> _objects;
	std::vector<std::shared_ptr<server::Player>> _players;
	std::vector<std::shared_ptr<server::Ghost>>  _ghosts;
	std::vector<std::shared_ptr<server::Key>>    _keys;
	std::shared_ptr<server::Start>               _start;

	std::shared_ptr<TcpServer> _server;
	int                        _numOfPlayers{0};
	int                        _id{0};
};

#endif // GAME_H
