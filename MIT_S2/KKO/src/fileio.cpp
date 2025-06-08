/**
 * @file fileio.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of the FileIO class for reading and writing files.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "fileio.hpp"
#include "debug.hpp"

using namespace std;

FileIO::FileIO()
{
    _input = "";
    _output = "";
}

/**
 * @brief Construct a new File IO File
 *
 * @param input input file name
 * @param output output file name
 */
FileIO::FileIO(Arguments &args)
{
    _input = args.getFileIn();
    _output = args.getFileOut();
    _inputSize = getFileSize(_input);
    _adaptiveFlag = args.isAdaptive();
    createHeader(args);
}

/**
 * @brief Reads the file and returns its contents as a vector of uint8_t.
 *
 * @return std::vector<uint8_t>
 */
vector<uint8_t> FileIO::readFile()
{
    ifstream file(_input, ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + _input);
    }
    vector<uint8_t> buffer(_inputSize);

    file.read(reinterpret_cast<char *>(buffer.data()), _inputSize);
    if (!file)
    {
        throw std::runtime_error("Error reading file: " + _input);
    }

    file.close();
    return buffer;
}

/**
 * @brief Returns the size of the file in bytes.
 *
 * @param filename
 * @return uint32_t
 */
uint32_t FileIO::getFileSize(const std::string &filename)
{
    std::ifstream file(filename,
                       std::ios::binary | std::ios::ate); // Open in binary mode and seek to the end
    if (!file)
    {
        cerr << "Error opening file: " << _input << endl;
        throw std::runtime_error("Failed to open file to get size: " + filename);
    }
    return static_cast<uint32_t>(
        file.tellg()); // Get the current position in the file (which is the size)
}

void FileIO::writeCompressedFile(std::vector<compressor::CompressedBlock> &compressedBlocks)
{
    ofstream file(_output, ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + _output);
    }

    // Write 4-byte header
    file.write(reinterpret_cast<const char *>(&_header), sizeof(_header));

    uint16_t blockCount = compressedBlocks.size();
    DEBUG_LOG("Block count: " << blockCount << endl);
    file.write(reinterpret_cast<const char *>(&blockCount), sizeof(blockCount));

    // Create flags
    createFlags(compressedBlocks);
    createCompressedFlags(compressedBlocks);
    if (_adaptiveFlag)
    {
        file.write(reinterpret_cast<const char *>(_adaptive.data()), _adaptive.size());
    }

    file.write(reinterpret_cast<const char *>(_compressed.data()), _compressed.size());

    // Write the compressed blocks
    for (const auto &block : compressedBlocks)
    {
        if (block.compressed) // check if block is compressed or not
        {
            uint16_t tokenCount = block.tokens.size();

            file.write(reinterpret_cast<const char *>(&tokenCount), sizeof(tokenCount));
            for (const auto &token : block.tokens)
            {
                file.write(reinterpret_cast<const char *>(&token), sizeof(token));
            }
        }
        else // Write raw data
        {
            uint16_t dataSize = block.data.size();
            file.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));
            file.write(reinterpret_cast<const char *>(block.data.data()), dataSize);
        }
    }

    if (!file)
    {
        throw std::runtime_error("Error writing to file: " + _output);
    }
}

void FileIO::createHeader(Arguments &args)
{
    _header |= static_cast<uint32_t>(args.getWidth()) << 16;
    uint16_t flags = 0;
    if (args.isModel()) // Set flags
    {
        flags |= 0b1; // Set the first bit to 1
    }
    if (args.isAdaptive())
    {
        flags |= 0b10; // Set the second bit to 1
    }
    _header |= flags;
}

void FileIO::createFlags(std::vector<compressor::CompressedBlock> &compressedBlocks)
{
    int counter = 0;
    uint8_t flags = 0;
    for (const auto &block : compressedBlocks)
    {
        if (block.scan_direction == ScanDirection::Vertical)
        {
            flags |= (1 << (7 - counter)); // MSB-first
        }
        // else do nothing — bit remains 0 for horizontal

        counter++;
        if (counter == 8)
        {
            _adaptive.push_back(flags);
            flags = 0;
            counter = 0;
        }
    }

    if (counter > 0)
    {
        _adaptive.push_back(flags); // Store last partial byte
    }
}

void FileIO::createCompressedFlags(std::vector<compressor::CompressedBlock> &compressedBlocks)
{
    int counter = 0;
    uint8_t flags = 0;
    for (const auto &block : compressedBlocks)
    {
        if (block.compressed)
        {
            flags |= (1 << (7 - counter)); // MSB-first
        }
        // else do nothing — bit remains 0 for uncompressed

        counter++;
        if (counter == 8)
        {
            _compressed.push_back(flags);
            flags = 0;
            counter = 0;
        }
    }

    if (counter > 0)
    {
        _compressed.push_back(flags); // Store last partial byte
    }
}

void FileIO::writeDecompressedFile(std::vector<uint8_t> &decompressedData)
{
    ofstream file(_output, ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + _output);
    }
    file.write(reinterpret_cast<const char *>(decompressedData.data()), decompressedData.size());
    file.close();
}