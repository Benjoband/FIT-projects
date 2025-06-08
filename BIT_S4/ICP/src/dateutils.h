/**
 * @file dateutils.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for date functions
 * @version 1.0
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <string>
#include <QDateTime>

namespace dateUtils {
    /**
     * @brief Get the Current Date and time for name of the logging file
     * 
     * @return std::string 
     */
    std::string getCurrentDateTimeString();
}

#endif // DATEUTILS_H