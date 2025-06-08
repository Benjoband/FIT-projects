/**
 * @file message.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Main class for messages, used for communication between server and client
 * @version 1.0
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "message.h"

#include <unordered_map>

using namespace communication;

constexpr char SEPARATOR{'_'};

const std::unordered_map<Message::Type, std::string> messageTypeToString{
    {Message::Type::Map, "Map"},
    {Message::Type::Score, "Score"},
    {Message::Type::Keys, "Keys"},
    {Message::Type::Direction, "Direction"},
    {Message::Type::Ending, "Ending"},
    {Message::Type::ClientId, "ClientId"},
};
const std::unordered_map<std::string, Message::Type> stringToMessageType{
    {messageTypeToString.at(Message::Type::Map), Message::Type::Map},
    {messageTypeToString.at(Message::Type::Score), Message::Type::Score},
    {messageTypeToString.at(Message::Type::Keys), Message::Type::Keys},
    {messageTypeToString.at(Message::Type::Direction), Message::Type::Direction},
    {messageTypeToString.at(Message::Type::Ending), Message::Type::Ending},
    {messageTypeToString.at(Message::Type::ClientId), Message::Type::ClientId}};

Message::Message(Type t) : _type{t} {
}

Message::Type Message::type() const {
	return _type;
}

std::string Message::getMessage() const {
	return _message;
}

std::string Message::getPayload() const {
	return _body;
}

std::string Message::serialize() const {
	return messageTypeToString.at(_type) + SEPARATOR;
}

Message Message::createFromString(const std::string& msg) {
	const std::string typeString{msg.substr(0, msg.find(SEPARATOR))};
	Type              type{stringToMessageType.at(typeString)};

	Message m{type};
	m.deserialize(msg);
	return m;
}

void Message::deserialize(const std::string& msg) {
	const std::string typeString{msg.substr(0, msg.find(SEPARATOR))};
	_message = msg;
	_body    = msg.substr(typeString.length() + 1);
}
