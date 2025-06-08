/**
 * @file message.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of Message class
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef COMMMESSAGE_H
#define COMMMESSAGE_H

#include <string>
#include <vector>

namespace communication {

/**
 * @brief Class for Message, including type and body and whole message, can serialize and deserialize string to message type
 * 
 */
class Message {
public:
	// enum class for message types
	enum class Type { Map, Score, Keys, Direction, Ending, ClientId, Invalid };

	// Constructor
	explicit Message(Type t);

	// Getter
	Type        type() const;
	std::string getMessage() const;
	std::string getPayload() const;

	/**
	 * @brief Serializes message
	 * 
	 * @return std::string 
	 */
	virtual std::string serialize() const;

	// When deserializing, you need to deserialize, check type and then promote
	/**
	 * @brief Creates message from string
	 * 
	 * @return Message 
	 */
	static Message createFromString(const std::string&);

	/**
	 * @brief Deserializes message
	 * 
	 */
	virtual void deserialize(const std::string&);

	/**
	 * @brief Promotes message to certain type
	 * 
	 * @tparam T 
	 * @return T 
	 */
	template<typename T>
	T promoteTo() {
		T promoted;
		promoted.deserialize(_body);
		return promoted;
	}

private:
	std::string _message; // Type + body
	Type        _type;
	std::string _body;
};

} // namespace communication

#endif // COMMMESSAGE_H
