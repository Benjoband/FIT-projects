/**
 * @file dateutils.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Source file for dateutils.h
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "dateutils.h"  

std::string dateUtils::getCurrentDateTimeString()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    for(int i  = 0; i < currentDateTimeString.length(); i++){
        if(currentDateTimeString[i] == ' ')
            currentDateTimeString[i] = '_';
        else if(currentDateTimeString[i] == ':')
            currentDateTimeString[i] = '-';
    }
    return currentDateTimeString.toStdString();
}
