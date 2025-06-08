/**
 * @file client.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file of TcpClient class
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QUrl>

#include "communication/client_id.h"
#include "communication/direction_message.h"
#include "communication/ending_message.h"
#include "communication/client_id.h"
#include "communication/keys_message.h"
#include "communication/map_message.h"
#include "communication/message.h"
#include "communication/score_message.h"

/**
 * @brief The TcpClient class for communication with server
 * 
 */
class TcpClient : public QObject {
	//Macro for signals and slots
	Q_OBJECT

public:
	// Constructor
	explicit TcpClient(QString target);

	// Setter
	void set_id(int id);

	// Getter
	int get_id() const;

public slots:
	/**
	 * @brief Send new message to server
	 * 
	 * @param message 
	 */
	void send_new_message(QString message);
	/**
	 * @brief Serialize and then send new message to server
	 * 
	 * @param message 
	 */
	void send_message(communication::Message* message);

signals:
	/**
	 * @brief Signal for sending message to server
	 * 
	 * @param msg 
	 */

	void message(QString msg);
	/**
	 * @brief Signal for receiving message from server
	 * 
	 * @param msg 
	 */

	void message_received(communication::Message msg);
	/**
	 * @brief Signal for receiving map message from server
	 * 
	 * @param msg 
	 */

	void map_message_received(communication::MapMessage msg);
	/**
	 * @brief Signal for receiving score message from server
	 * 
	 * @param msg 
	 */

	void score_message_received(communication::ScoreMessage msg);
	/**
	 * @brief Signal for receiving keys message from server
	 * 
	 * @param msg 
	 */
	
	void keys_message_received(communication::KeysMessage msg);
	/**
	 * @brief Signal for receiving ending message from server
	 * 
	 * @param msg 
	 */
	void ending_message_received(communication::EndingMessage msg);

private slots:
	/**
	 * @brief Slot for getting new message from server
	 * 
	 */
	void getting_message();
	/**
	 * @brief Slot for deleting socket
	 * 
	 */
	void deleteSocket();

private:
	QTcpSocket* socket{};
	int _id;
};

#endif // CLIENT_H
