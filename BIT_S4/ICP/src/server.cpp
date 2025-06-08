/**
 * @file server.cpp
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Implementation of server.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "server.h"

using namespace communication;

TcpServer::TcpServer(uint16_t port) {
	server = new QTcpServer(this);
	connect(server, &QTcpServer::newConnection, this, &TcpServer::new_connection);


	if (!server->listen(QHostAddress::Any, port)) {
		qFatal("An error occured when trying to set up a server");
	}

	connect(this, &TcpServer::message, [this](QString msg) {
		try {
			Message mess{Message::createFromString(msg.toStdString())};
			emit    message_received(mess);
		} catch (std::out_of_range& oor) {
			qDebug() << "Invalid message " << msg;
		}
	});

	connect(this, &TcpServer::message_received, [this](Message msg) {
		switch (msg.type()) {
		case Message::Type::Direction: {
			auto directionMsg = msg.promoteTo<DirectionMessage>();
			emit direction_message_received(directionMsg.getDirection(), directionMsg.getId());
        } break;}
	});

}

TcpServer::~TcpServer() {
	for (auto* socket : sockets) {
		socket->close();
		socket->deleteLater();
	}
	server->close();
	server->deleteLater();
}

void TcpServer::setIdGenerator(IdGenerator generator) {
	_idGenerator = generator;
}

void TcpServer::new_connection() {
	auto socket = server->nextPendingConnection();
	prepare_socket(socket);
	sockets.append(socket);
}

void TcpServer::prepare_socket(QTcpSocket* socket) {
	connect(socket, &QTcpSocket::readyRead, [this, socket]() { getting_message(socket); });
	connect(socket, &QTcpSocket::disconnected, [this, socket]() { deleteSocket(socket); });

	auto clientId = _idGenerator();

	ClientIdMessage msg;
	msg.setClientId(clientId);

	send_message_one(socket, &msg);
}

void TcpServer::getting_message(QTcpSocket* socket) {
	while (socket->bytesAvailable() > 0) {
		QByteArray  buffer;
		QDataStream socketStream(socket);
		socketStream >> buffer;

		emit message(buffer);
	}
}

void TcpServer::send_new_message_all(QString message) {
	for (auto* socket : sockets) {
		send_new_message_one(socket, message);
	}
}

void TcpServer::send_new_message_one(QTcpSocket* socket, QString message) {
	if (socket->isOpen()) {
		QDataStream dstream(socket);
		const QByteArray sendbuff = message.toUtf8();
		dstream << sendbuff;

		if (!socket->waitForBytesWritten()) {
			qDebug() << "Error sending message";
		}
	} else {
		qFatal("Socket does not seem to be opened");
	}
}

void TcpServer::send_message(Message* message) {
	std::string content = message->serialize();
	send_new_message_all(QString::fromStdString(content));
	emit messageSent(content);
}

void TcpServer::send_message_one(QTcpSocket* socket, communication::Message* message) {
	const std::string content = message->serialize();
	send_new_message_one(socket, QString::fromStdString(content));
}

void TcpServer::deleteSocket(QTcpSocket* socket) {
	sockets.removeOne(socket);
}
