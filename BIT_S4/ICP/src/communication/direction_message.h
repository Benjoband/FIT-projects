/**
 * @file direction_message.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of DirectionMessage class, inheriting from Message class
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DIRECTIONMESSAGE_H
#define DIRECTIONMESSAGE_H

#include "message.h"
#include "../server_objects/object.h"

namespace communication {

/**
 * @brief Class for DirectionMessage, including id,direction and own serialize and deserialize methods
 * 
 */
class DirectionMessage : public Message {
public:
    using Direction = server::Object::Direction;

	// Constructor
	DirectionMessage();

	// Getters
    Direction getDirection() const;
	int getId() const;

	// Setters
    void setDirection(Direction direction);
	void setId(int id);

	std::string serialize() const override;
	void        deserialize(const std::string&) override;

private:
	Direction _direction = Direction::UP;
	int id{0};
};

} // namespace communication

#endif // KEYSMESSAGE_H
