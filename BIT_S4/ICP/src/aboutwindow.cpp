/**
 * @file aboutwindow.cpp
 * @author Samuel Čus (xcussa00)
 * @brief About window
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "aboutwindow.h"
#include "./ui_aboutwindow.h"


AboutWindow::AboutWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AboutWindow)
{
    ui->setupUi(this);


}
AboutWindow::~AboutWindow()
{
    delete ui;
}


