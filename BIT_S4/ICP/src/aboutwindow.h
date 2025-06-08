/**
 * @file aboutwindow.h
 * @author Samuel Čus (xcussa00)
 * @brief About window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AboutWindow; }
QT_END_NAMESPACE

class AboutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow() override;
    Ui::AboutWindow *ui{nullptr};
};

#endif // ABOUTWINDOW_H
