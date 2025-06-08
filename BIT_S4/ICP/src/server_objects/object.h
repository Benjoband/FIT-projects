/**
 * @file object.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for map objects like player, ghost and start
 * @version 1.0
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SERVER_OBJECT_H
#define SERVER_OBJECT_H

#include "noncopyable.h"
#include <memory>
#include <string>
#include <vector>

class Map;
class Game;

namespace server {

/**
 * @brief Object class for player and ghosts
 * 
 */
class Object : NonCopyable {
public:
	enum class Direction { UP = 0, RIGHT, DOWN, LEFT };

	// Constructors
	Object();
	Object(int newX, int newY, int newNumber);
	virtual ~Object() = default;

	// Getters
	int getX() const;
	int getY() const;
	int                   getNumber() const;
	std::shared_ptr<Map>  getMap() const;
	std::shared_ptr<Game> getGame() const;

	// Setters
	void setX(int newX);
	void setY(int newY);
	void setNumber(int newNumber);
	void setMap(std::shared_ptr<Map> map);
	void setGame(std::shared_ptr<Game> game);

	/**
	 * @brief Every world tick means one move in game. Moves all objects in game.
	 * 
	 */
	virtual void        worldTick()               = 0;

	/**
	 * @brief Returns string representation of object, used for logging
	 * 
	 * @return std::string 
	 */
	virtual std::string toString() const          = 0;
	
	/**
	 * @brief Returns char representation of object, used in map
	 * 
	 * @return char 
	 */
	virtual char        mapRepresentation() const = 0;

	/**
	 * @brief Checks the rules if object coliides with other objects
	 * 
	 * @param objects 
	 * @return int 
	 */
	virtual int 	    collision(std::vector<std::shared_ptr<server::Object>> objects) = 0;

private:
	int                   _x{0};
	int                   _y{0};
	int                   _number{0};
	std::shared_ptr<Map>  _map;
	std::shared_ptr<Game> _game;
};

} // namespace server

#endif // SERVER_OBJECT_H
