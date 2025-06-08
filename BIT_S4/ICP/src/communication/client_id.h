/**
 * @file client_id.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of ClientIdMessage class, inheriting from Message class
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CLIENT_ID_H
#define CLIENT_ID_H

#include "message.h"

namespace communication {

/**
 * @brief Class for ClientIdMessage, including id and own serialize and deserialize methods
 * 
 */
class ClientIdMessage : public Message {
public:
	// Constructor
	ClientIdMessage();

	// Getter
	size_t getClientId() const;

	// Setter
	void   setClientId(size_t id);

	std::string serialize() const override;
	void        deserialize(const std::string&) override;

private:
	size_t _id{0};
};

} // namespace communication

#endif // CLIENT_ID_H
