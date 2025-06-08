/**
 * @file keys_message.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of KeyMessage class, inheriting from Message class
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef KEYSMESSAGE_H
#define KEYSMESSAGE_H

#include "message.h"

namespace communication {

/**
 * @brief Class for KeysMessage, including collected keys and number of keys to win and own serialize and deserialize methods
 * 
 */
class KeysMessage : public Message {
public:
    // Constructor
	KeysMessage();

    // Getters
    int getCollected() const;
    int getNumKeysToWin() const;

    // Setters
    void setCollected(int collected);
    void setNumKeysToWin(int numKeysToWin);

	std::string serialize() const override;
	void        deserialize(const std::string&) override;

private:
	int _collected{0};
    int _numKeysToWin{0};
};

} // namespace communication

#endif // KEYSMESSAGE_H
