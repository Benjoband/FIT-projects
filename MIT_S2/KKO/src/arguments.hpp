/**
 * @file arguments.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Argument parsing for the program
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <cstdint>
#include <string>

/**
 * @brief Class for reading and storing command line arguments used for the program control.
 *
 */
class Arguments
{
    public:
        Arguments();
        Arguments(int argc, char *argv[]);

        ~Arguments() = default;

        std::string getFileOut() const;
        std::string getFileIn() const;
        bool isCompress() const;
        bool isModel() const;
        bool isAdaptive() const;
        uint16_t getWidth() const;

        void printHelp() const;

    private:
        std::string _fileOut;
        std::string _fileIn;

        bool _compress; // True if compressing, false if decompressing
        bool _model;    // True for usage of model
        bool _adaptive; //

        uint16_t _width;
};

#endif