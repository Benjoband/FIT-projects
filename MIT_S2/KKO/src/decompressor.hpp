/**
 * @file decompressor.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for implementation of LZ77 decompression algorithm
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef DECOMPRESSOR_HPP
#define DECOMPRESSOR_HPP

#include "arguments.hpp"
#include "compressor.hpp"
#include "scanner.hpp"
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

/**
 * @brief Class for decompressing LZ77 compressed data with custom made header and more information.
 *
 */
class Decompressor
{
    public:
        /**
         * @brief Construct a new Decompressor object and initialize it with header from the input
         * file.
         *
         * @param args
         */
        Decompressor(Arguments &args);
        ~Decompressor();

        /**
         * @brief Read and decompress the blocks from the input file.
         *
         */
        void decompressBlocks();

        /**
         * @brief Get the Decompressed Data object
         *
         * @return std::vector<uint8_t>
         */
        std::vector<uint8_t> getDecompressedData();

        bool getModel() const;

    private:
        std::string _input;

        std::ifstream _inputFile;

        uint16_t _width;
        bool _adaptive;
        bool _model;

        uint16_t _blockCount;

        std::vector<uint8_t> _adaptiveFlags;
        std::vector<uint8_t> _compressionFlags;

        std::vector<uint8_t> _decompressedData;

        /**
         * @brief Parse and decompress the tokens from the input file.
         *
         * @param tokens
         * @param expectedSize
         * @return std::vector<uint8_t>
         */
        std::vector<uint8_t> decompressLZ77(const std::vector<compressor::LZ77Token> &tokens,
                                            std::size_t expectedSize);
        bool getFlagBit(const std::vector<uint8_t> &flags, int index);

        /**
         * @brief Write decompressed data to the image buffer.
         *
         * @param serialized
         * @param x
         * @param y
         * @param dir
         */
        void writeBlockToBuffer(const std::vector<uint8_t> &serialized, int x, int y,
                                ScanDirection dir);
};

#endif // DECOMPRESSOR_HPP