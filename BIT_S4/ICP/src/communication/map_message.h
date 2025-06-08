/**
 * @file map_message.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of MapMessage class, inheriting from Message class
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MAPMESSAGE_H
#define MAPMESSAGE_H

#include "message.h"

namespace communication {

/**
 * @brief Class for MapMessage, including map data and own serialize and deserialize methods
 * 
 */
class MapMessage : public Message {
public:
	// Constructor
	MapMessage();

	// Getters
	std::vector<std::vector<char>> getMapData() const;
	int  						   getHeight() const;
	int 						   getWidth() const;

	// Setter
	void setMapData(const std::vector<std::vector<char>>& mapData);

	/**
	 * @brief Clear map data
	 * 
	 */
	void clearMapData();

	std::string serialize() const override;
	void        deserialize(const std::string&) override;

private:
	std::vector<std::vector<char>> _mapData;
};

} // namespace communication

#endif // MAPMESSAGE_H
