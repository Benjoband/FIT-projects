/**
 * @file ghost.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @author Patrik Olszar (xolsza00@stud.fit.vutbr.cz)
 * @brief Header file of ghost class, inheriting from object class
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SERVER_GHOST_HPP
#define SERVER_GHOST_HPP

#include "object.h"

namespace server {

/**
 * @brief Ghost class, including current tile under the ghost, ghosts position and number
 * 
 */
class Ghost : public Object {
public:
	// Constructors
	Ghost();
	Ghost(int posX, int posY, int number);

	Direction getDirection() const;
	void      setDirection(Direction dir);

	/**
	 * @brief Get the new direction for ghost, change to random free direction
	 * 
	 * @param x 
	 * @param y 
	 * @return Direction 
	 */
	Direction getNewDirection(int x,int y);

	// Inherited methods
	void worldTick() override;
	std::string toString() const override;
	char mapRepresentation() const override;
	int 	    collision(std::vector<std::shared_ptr<server::Object>> objects) override;

private:
	Direction _direction{Direction::RIGHT};
};

} // namespace server

#endif // SERVER_GHOST_HPP
