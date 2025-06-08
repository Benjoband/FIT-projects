/**
 * @file playwindow.h
 * @author Samuel Čus (xcussa00)
 * @brief Play window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayWindow; }
QT_END_NAMESPACE

class PlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = nullptr);
    ~PlayWindow() override;
    Ui::PlayWindow *ui{nullptr};
};

#endif // PLAYWINDOW_H
