/**
 * @file client.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of client.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "client.h"
#include <stdexcept>

using namespace communication;

TcpClient::TcpClient(QString targetString) : socket{new QTcpSocket(this)} {
	connect(socket, &QTcpSocket::readyRead, this, &TcpClient::getting_message);
	connect(socket, &QTcpSocket::disconnected, this, &TcpClient::deleteSocket);

	QUrl target{"http://" + targetString};

	if (target.host() != "0.0.0.0") {
		qDebug() << "Connecting to " << target << target.host() << target.port();
		socket->connectToHost(target.host(), target.port());
    }

	if (!(socket->waitForConnected(1000))) {
		qFatal("Timeout error");
		exit(EXIT_FAILURE);
	}

	connect(this, &TcpClient::message, [this](QString msg) {
		try {
			Message mess{Message::createFromString(msg.toStdString())};
			emit    message_received(mess);
		} catch (std::out_of_range& oor) {
			qDebug() << "Invalid message " << msg;
		}
	});

	connect(this, &TcpClient::message_received, [this](Message msg) {
		switch (msg.type()) {
		case Message::Type::Map: {
			auto mapMsg = msg.promoteTo<MapMessage>();
			emit map_message_received(mapMsg);
		} break;
		case Message::Type::Score: {
			auto scoreMsg = msg.promoteTo<ScoreMessage>();	
			emit score_message_received(scoreMsg);
		} break;
		case Message::Type::Keys: {
			auto keysMsg = msg.promoteTo<KeysMessage>();
			emit keys_message_received(keysMsg);
		} break;
		case Message::Type::Ending: {
			auto endingMsg = msg.promoteTo<EndingMessage>();
			emit ending_message_received(endingMsg);
		} break;
		case Message::Type::ClientId: {
			auto clientIdMsg = msg.promoteTo<ClientIdMessage>();
			set_id(clientIdMsg.getClientId());
		} break;
		default:
			break;
		}
	});
}

void TcpClient::set_id(int id) {
	_id = id;
}

int TcpClient::get_id() const {
    return _id;
}

void TcpClient::getting_message() {
	auto* socket = qobject_cast<QTcpSocket*>(sender());

	while (socket->bytesAvailable() > 0) {
		QByteArray  buffer;
		QDataStream socketStream(socket);
		socketStream >> buffer;

		emit message(buffer);
	}
}

void TcpClient::deleteSocket() {
	socket->deleteLater();
}

void TcpClient::send_new_message(QString message) {
	if (socket) {
		if (socket->isOpen()) {
			QDataStream      socketStream(socket);
			const QByteArray array = message.toUtf8();
			socketStream << array;

			if (!socket->waitForBytesWritten()) {
				qFatal("Timeout error");
			}
		} else {
			qWarning("Socket does not seem to be opened");
		}
	} else {
		qFatal("Not connected");
	}
}

void TcpClient::send_message(communication::Message* message) {
	const std::string content = message->serialize();
	send_new_message(QString::fromStdString(content));
}


