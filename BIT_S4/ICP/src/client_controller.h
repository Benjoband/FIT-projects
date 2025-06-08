/**
 * @file client_controller.h
 * @author Patrik Olszar (xolsza00@fit.vutbr.cz)
 * @brief Header file for ClienController class, inheriting from QObject
 * @version 1.0
 * @date 2023-05-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include "client.h"
#include "playwindow.h"
#include "./communication/ending_message.h"
#include "ui_gamewindow.h"

#include <QGraphicsScene>
#include <QObject>
#include <memory>

#include "server_objects/object.h"

class ClientController : public QObject
{
	Q_OBJECT

	using Ending = communication::EndingMessage::Ending;
public:

	/**
	 * @brief Construct a new Client Controller object
	 * 
	 * @param parent 
	 */
	explicit ClientController(QObject* parent = nullptr);

	// Setters
	void setView(QGraphicsView*);
	void setClient(std::shared_ptr<TcpClient> client);
	void setUi(Ui::GameWindow* ui);

	using Direction = server::Object::Direction;

public:
	/**
	 * @brief Set the Map Data 
	 * 
	 * @param mapData 
	 */
	void setMapData(std::vector<std::vector<char>> mapData);
	/**
	 * @brief Set the Score
	 * 
	 * @param score 
	 * @param id 
	 */
	void setScore(int score, int id);
	/**
	 * @brief Set the Keys
	 * 
	 * @param collected 
	 * @param total 
	 */
	void setKeys(int collected, int total);
	/**
	 * @brief Set the Ending
	 * 
	 * @param state 
	 */
	void setEnding(Ending state);

public slots:
	/**
	 * @brief Key pressed slot
	 * 
	 * @param d 
	 */
	void keyPressed(Direction d);

private:
	/**
	 * @brief Event filter
	 * 
	 * @param object 
	 * @param event 
	 * @return true 
	 * @return false 
	 */
	bool eventFilter(QObject* object, QEvent* event);

private:
	QGraphicsScene* _scene{};
	QGraphicsView*  _view{};
	std::shared_ptr<TcpClient> _client;
	Ui::GameWindow* _ui;
};

#endif // CLIENTCONTROLLER_H
