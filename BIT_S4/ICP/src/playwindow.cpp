/**
 * @file playwindow.cpp
 * @author Samuel Čus (xcussa00)
 * @brief Play window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "playwindow.h"
#include "./ui_playwindow.h"

PlayWindow::PlayWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayWindow)
{
    ui->setupUi(this);


}
PlayWindow::~PlayWindow()
{
    delete ui;
}



