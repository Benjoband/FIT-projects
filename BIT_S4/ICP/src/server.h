/**
 * @file server.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of TcpServer class
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SERVER_H
#define SERVER_H

#include <functional>
#include <QDebug>
#include <QString>
#include <QtCore>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "communication/map_message.h"
#include "communication/score_message.h"
#include "communication/keys_message.h"
#include "communication/direction_message.h"
#include "communication/ending_message.h"
#include "communication/message.h"

#include "communication/client_id.h"

#include "server_objects/object.h"

/**
 * @brief The TcpServer class, inheriting from QObject, for communication with clients
 */
class TcpServer : public QObject {
	//Macro for signals and slots
	Q_OBJECT

public:
    using Direction = server::Object::Direction;
	// Constructor
	explicit TcpServer(uint16_t port);
	~TcpServer() override;

	using IdGenerator = std::function<size_t()>;

	// Setters
	void setIdGenerator(IdGenerator generator);

public slots:
	/**
	 * @brief Send new message to all clients
	 * 
	 * @param message 
	 */
	void send_new_message_all(QString message);

	/**
	 * @brief Serialize and then send new message to all clients
	 * 
	 * @param message 
	 */
	void send_message(communication::Message* message);

	/**
	 * @brief Serialize and then send new message to one client
	 * 
	 * @param socket 
	 * @param message 
	 */
	void send_message_one(QTcpSocket* socket, communication::Message* message);

	/**
	 * @brief Send new message to one client
	 * 
	 * @param socket 
	 * @param message 
	 */
	void send_new_message_one(QTcpSocket* socket, QString message);
	
signals:
	/**
	 * @brief Signal for new message
	 * 
	 * @param msg 
	 */
	void message(QString msg);

	/**
	 * @brief Signal for received message
	 * 
	 * @param msg 
	 */
	void message_received(communication::Message msg);

	/**
	 * @brief Signal for received direction message
	 * 
	 * @param direction 
	 * @param id 
	 */
	void direction_message_received(Direction direction, size_t id);

	/**
	 * @brief Signal for sent message
	 * 
	 * @param message 
	 */
	void messageSent(std::string message);

private slots:
	/**
	 * @brief New connection slot
	 * 
	 */
	void        new_connection();
	/**
	 * @brief Prepare socket for communication
	 * 
	 * @param socket 
	 */
	void        prepare_socket(QTcpSocket* socket);
	/**
	 * @brief Get the message from socket
	 * 
	 * @param socket 
	 */
	void        getting_message(QTcpSocket* socket);
	/**
	 * @brief Delete socket from list
	 * 
	 * @param socket 
	 */
	void        deleteSocket(QTcpSocket* socket);

private:
	QTcpServer* server = nullptr;

	QList<QTcpSocket*> sockets;
	IdGenerator        _idGenerator;
};

#endif // SERVER_H
