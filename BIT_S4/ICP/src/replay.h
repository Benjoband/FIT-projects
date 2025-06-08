#ifndef REPLAY_H
#define REPLAY_H

#include "client.h"
#include <QTimer>
#include <QWidget>

namespace Ui {
class Replay;
}

class Replay : public QWidget
{
	Q_OBJECT

public:
	explicit Replay(QWidget* parent = nullptr);
	~Replay();

	void setTcpClient(std::shared_ptr<TcpClient> client);
	void loadCommands(QString filename);

public slots:
	void play();
	void pause();

	void forward();
	void backward();

private:
	void send();

private:
	Ui::Replay* ui;

	std::shared_ptr<TcpClient> _client;
	QTimer*                    _timer{};

	std::vector<std::vector<std::string>> _commands;
	size_t                                _commandsIndex{0};
};

#endif // REPLAY_H
