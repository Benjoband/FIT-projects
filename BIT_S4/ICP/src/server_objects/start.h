/**
 * @file start.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for start class inheriting from object
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SERVER_START_H
#define SERVER_START_H

#include "object.h"

namespace server {

/**
 * @brief Class for starting tile object, including start position
 * 
 */
class Start : public Object {
public:
	// Constructors
	Start(int x, int y, int id);

	// Inherited methods
	void        worldTick() override;
	std::string toString() const override;
	char        mapRepresentation() const override;
	int 	    collision(std::vector<std::shared_ptr<server::Object>>) override;
};

} // namespace server

#endif // SERVER_START_H
