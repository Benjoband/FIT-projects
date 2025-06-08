#include "replay.h"
#include "ui_replay.h"

#include "client.h"
#include "communication/message.h"
#include <fstream>
#include <iostream>
#include <QFileDialog>

Replay::Replay(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::Replay)
{
	ui->setupUi(this);
	_timer = new QTimer();
	_timer->setSingleShot(false);
	_timer->setInterval(500);

	connect(_timer, &QTimer::timeout, [this] { forward(); });

	connect(ui->loadButton, &QPushButton::clicked, [this] {
		QString logfile = QFileDialog::getOpenFileName(this);
		if (!logfile.isEmpty()) {
			loadCommands(logfile);
		}
	});

	connect(ui->forwardButton, &QPushButton::clicked, this, &Replay::forward);
	connect(ui->backButton, &QPushButton::clicked, this, &Replay::backward);
	connect(ui->playButton, &QPushButton::clicked, this, &Replay::play);
	connect(ui->pauseButton, &QPushButton::clicked, this, &Replay::pause);
}

Replay::~Replay()
{
	delete ui;
}

void Replay::setTcpClient(std::shared_ptr<TcpClient> client) {
	_client = client;
}

void Replay::loadCommands(QString filename) {
	pause();

	std::ifstream file(filename.toStdString());

	_commands.clear();

	std::vector<std::string> commandSet;

	std::clog << "READING LOGFILE " << filename.toStdString() << std::endl;

	std::string line;
	while (std::getline(file, line)) {
		std::clog << "LOGLINE: " << line.c_str() << std::endl;
		communication::Message m    = communication::Message::createFromString(line);

		if (!commandSet.empty() && m.type() == communication::Message::Type::Map) {
			_commands.push_back(commandSet);
			commandSet.clear();
		}
		commandSet.push_back(line);
	}
	_commands.push_back(commandSet);
	_commandsIndex = 0;
	send();
}

void Replay::play() {
	ui->playButton->setEnabled(false);
	ui->pauseButton->setEnabled(true);
	ui->forwardButton->setEnabled(false);
	ui->backButton->setEnabled(false);
	ui->loadButton->setEnabled(false);

	_timer->start();
}

void Replay::pause() {
	ui->playButton->setEnabled(true);
	ui->pauseButton->setEnabled(false);
	ui->forwardButton->setEnabled(true);
	ui->backButton->setEnabled(true);
	ui->loadButton->setEnabled(true);

	_timer->stop();
}

void Replay::forward() {
	if (_commands.empty()) {
		return;
	}

	if (_commandsIndex < _commands.size() - 1) {
		_commandsIndex++;
	}

	send();
}

void Replay::backward() {
	if (_commands.empty()) {
		return;
	}

	if (_commandsIndex > 0) {
		_commandsIndex--;
	}
	send();
}

void Replay::send() {
	if (_commands.empty()) {
		return;
	}

	for (auto command : _commands[_commandsIndex]) {
		_client->message(QString::fromStdString(command));
	}
	ui->label->setText(QString("Step %1 / %2").arg(_commandsIndex).arg(_commands.size()));
}
