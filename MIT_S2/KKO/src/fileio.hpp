/**
 * @file fileio.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for the FileIO class for reading and writing files.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "arguments.hpp"
#include "compressor.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Class for reading and writing files.
 */
class FileIO
{
    public:
        FileIO();
        FileIO(Arguments &args);

        /**
         * @brief Reads a file and returns its contents as a vector of bytes.
         *
         * @return std::vector<uint8_t>
         */
        std::vector<uint8_t> readFile();

        /**
         * @brief Computes the size of a file in bytes.
         *
         * @param filename file name to be read
         * @return uint32_t size of the file in bytes
         */
        uint32_t getFileSize(const std::string &filename);

        /**
         * @brief Writes a vector of blocks to a file.
         *
         * @param compressedBlocks Blocks to be written to the file
         */
        void writeCompressedFile(std::vector<compressor::CompressedBlock> &compressedBlocks);

        /**
         * @brief Writes decompressed data to a file.
         *
         * @param decompressedData Decompressed data to be written to the file
         */
        void writeDecompressedFile(std::vector<uint8_t> &decompressedData);

    private:
        std::string _input;
        std::string _output;
        uint32_t _inputSize;
        bool _adaptiveFlag = false;

        uint32_t _header = 0;
        std::vector<uint8_t> _adaptive;
        std::vector<uint8_t> _compressed;

        /**
         * @brief Create a header for the compressed file.
         *
         * @param args
         */
        void createHeader(Arguments &args);

        /**
         * @brief Create a header of direction flags for the compressed file.
         *
         * @param compressedBlocks
         */
        void createFlags(std::vector<compressor::CompressedBlock> &compressedBlocks);

        /**
         * @brief Create a header of compressed flags for the compressed file.
         *
         * @param compressedBlocks
         */
        void createCompressedFlags(std::vector<compressor::CompressedBlock> &compressedBlocks);
};

/**
 * ###HEADER###
 * 2 bytes: width | 2 bytes: flags | 2 bytes for number of blocks
 *
 * Width/16*16 bits of flags for direction of scan for each block
 * Then width/16*16 bits of flags if data is compressed
 */

#endif // FILEIO_HPP
