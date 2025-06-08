/**
 * @file player.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for player class inheriting from object
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "object.h"

namespace server {

/**
 * @brief Player class, including current direction, position, score and number
 * 
 */
class Player : public Object {
public:
	// Constructors
	Player(int newX, int newY, int objectId, int playerId);

	// Getters
	Direction 	getDirection() const;
	int       	getScore() const;
	int 		getPlayerId() const;

	// Setters
	void setDirection(Direction newDirection);
	void setScore(int newScore);

	// Inherited methods
	void worldTick() override;
	std::string toString() const override;
	char mapRepresentation() const override;
	int collision(std::vector<std::shared_ptr<server::Object>> objects) override;

private:
	Direction direction{Direction::RIGHT};
	int       score{0};
	int       playerId{0};
};

} // namespace server

#endif // SERVER_PLAYER_H
