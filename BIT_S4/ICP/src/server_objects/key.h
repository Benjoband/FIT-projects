/**
 * @file key.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for key class inheriting from object
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SERVER_KEY_H
#define SERVER_KEY_H

#include "object.h"

namespace server {

/**
 * @brief Class for key object, including key number
 * 
 */
class Key : public Object {
public:
	// Constructors
	Key(int posX, int posY, int number);

	//	Inherited methods
	void        worldTick() override;
	std::string toString() const override;
	char        mapRepresentation() const override;
	int 	    collision(std::vector<std::shared_ptr<server::Object>>) override;

	/**
	 * @brief If player takes key, it shouldnt be visible on map anymore, so this is used to check if key is taken
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isTaken() const;

	/**
	 * @brief Sets _taken to true if key is taken
	 * 
	 * @param taken 
	 */
	void setTaken(bool taken);
private:
	bool _taken{false};
};

} // namespace server

#endif // SERVER_KEY_H
