/**
 * @file arguments.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Argument parsing for the program
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "arguments.hpp"
#include <iostream>

using namespace std;

Arguments::Arguments()
{
    _fileOut = "";
    _fileIn = "";

    _compress = false;
    _model = false;
    _adaptive = false;

    _width = 0;
}

Arguments::Arguments(int argc, char *argv[])
{
    _fileOut = "";
    _fileIn = "";

    _compress = false;
    _model = false;
    _adaptive = false;

    _width = 0;

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "-o")
        {
            _fileOut = argv[++i];
        }
        else if (arg == "-i")
        {
            _fileIn = argv[++i];
        }
        else if (arg == "-c")
        {
            _compress = true;
        }
        else if (arg == "-d")
        {
            _compress = false;
        }
        else if (arg == "-m")
        {
            _model = true;
        }
        else if (arg == "-a")
        {
            _adaptive = true;
        }
        else if (arg == "-w")
        {
            _width = stoul(argv[++i]);
        }
        else
        {
            cerr << "Unknown argument: " << arg << endl;
            exit(1);
        }
    }
    if (_fileOut.empty())
    {
        cerr << "Output file not specified. Use -o <filename>" << endl;
        printHelp();
        exit(1);
    }
    if (_fileIn.empty())
    {
        cerr << "Input file not specified. Use -i <filename>" << endl;
        printHelp();
        exit(1);
    }
    if (_width == 0 && _compress == 1)
    {
        cerr << "Width not specified. Use -w <width>" << endl;
        printHelp();
        exit(1);
    }
    // TODO?
}

string Arguments::getFileOut() const { return _fileOut; }

string Arguments::getFileIn() const { return _fileIn; }

bool Arguments::isCompress() const { return _compress; }

bool Arguments::isModel() const { return _model; }

bool Arguments::isAdaptive() const { return _adaptive; }

uint16_t Arguments::getWidth() const { return _width; }

void Arguments::printHelp() const
{
    cout << "Usage: program [options]" << endl;
    cout << "Options:" << endl;
    cout << "  -o <filename>   Output file" << endl;
    cout << "  -i <filename>   Input file" << endl;
    cout << "  -c              Compress" << endl;
    cout << "  -d              Decompress" << endl;
    cout << "  -m              Use model" << endl;
    cout << "  -a              Adaptive" << endl;
    cout << "  -w <width>      Width" << endl;
}