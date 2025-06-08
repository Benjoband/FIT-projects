/**
 * @file decompressor.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of decompressor of LZ77 compressed data with custom made header and more
 * information.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "decompressor.hpp"
#include "debug.hpp"
#include "model.hpp"
#include <iostream>

using namespace std;

Decompressor::Decompressor(Arguments &args)
    : _input(args.getFileIn()), _inputFile(_input, ios::binary) //, _output(args.getFileIn())
{
    if (!_inputFile)
    {
        cerr << "Error opening input file: " << _input << endl;
        exit(1);
    }
    // Read the header - 2 bytes for width and 2 bytes for flags
    uint32_t header = 0;
    _inputFile.read(reinterpret_cast<char *>(&header), sizeof(header));
    _width = static_cast<uint16_t>(header >> 16);
    uint16_t flags = static_cast<uint16_t>(header & 0xFFFF);
    _adaptive = (flags & 0b10) != 0;
    _model = (flags & 0b1) != 0;

    // Read 2-byte block count
    _inputFile.read(reinterpret_cast<char *>(&_blockCount), sizeof(_blockCount));
    int flagBytes = (_blockCount + 7) / 8;

    // Read adaptive flags if present
    if (_adaptive)
    {
        _adaptiveFlags.resize(flagBytes);
        _inputFile.read(reinterpret_cast<char *>(_adaptiveFlags.data()), flagBytes);
    }

    // Read compression flags
    _compressionFlags.resize(flagBytes);
    _inputFile.read(reinterpret_cast<char *>(_compressionFlags.data()), flagBytes);

    DEBUG_LOG("Decompressor initialized. Width: " << _width << ", Blocks: " << _blockCount
                                                  << ", Adaptive: " << _adaptive
                                                  << ", Model: " << _model << '\n');
}

Decompressor::~Decompressor() = default;

bool Decompressor::getModel() const { return _model; }

void Decompressor::decompressBlocks()
{
    uint16_t BLOCK_SIZE = (_adaptive) ? 16 : _width;
    std::size_t expectedSize = BLOCK_SIZE * BLOCK_SIZE;
    uint32_t imageSize = _width * _width;

    DEBUG_LOG("Decompressing blocks. Width: " << _width << ", Block size: " << BLOCK_SIZE
                                              << ", Expected size: " << expectedSize
                                              << ", Image size: " << imageSize << '\n');

    uint16_t blocksPerRow = _width / BLOCK_SIZE;
    uint16_t totalBlocks = (_adaptive) ? blocksPerRow * blocksPerRow : 1;

    _decompressedData.resize(imageSize); // Initialize to the size of the image
    DEBUG_LOG("Decompressing " << totalBlocks << " block(s)\n");

    for (uint16_t blockIndex = 0; blockIndex < totalBlocks; ++blockIndex) // Go through all blocks
    {
        // Read flags
        ScanDirection dir = ScanDirection::Horizontal;
        if (_adaptive)
        {
            bool isVertical = getFlagBit(_adaptiveFlags, blockIndex);
            dir = isVertical ? ScanDirection::Vertical : ScanDirection::Horizontal;
        }

        bool isCompressed = getFlagBit(_compressionFlags, blockIndex);
        std::vector<uint8_t> serialized;

        if (isCompressed) // Decompress
        {
            uint16_t tokenCount;
            _inputFile.read(reinterpret_cast<char *>(&tokenCount), sizeof(tokenCount));

            std::vector<compressor::LZ77Token> tokens(tokenCount);
            _inputFile.read(reinterpret_cast<char *>(tokens.data()),
                            tokenCount * sizeof(compressor::LZ77Token));

            serialized = decompressLZ77(tokens, expectedSize);
        }
        else // Not compressed
        {
            uint16_t rawSize;
            _inputFile.read(reinterpret_cast<char *>(&rawSize), sizeof(rawSize));

            serialized.resize(rawSize);
            _inputFile.read(reinterpret_cast<char *>(serialized.data()), rawSize);
        }

        // Undo model if needed
        if (_model)
        {
            DEBUG_LOG("Undoing model: " << _model);
            model::undoModel(serialized);
        }

        // Write into image buffer
        if (_adaptive)
        {
            int blockX = (blockIndex % blocksPerRow) * BLOCK_SIZE;
            int blockY = (blockIndex / blocksPerRow) * BLOCK_SIZE;
            writeBlockToBuffer(serialized, blockX, blockY, dir);
        }
        else // Write just one block
        {
            DEBUG_LOG("No adaptive, saving single block \n");
            _decompressedData = serialized;
        }
    }

    DEBUG_LOG("Decompressed data size: " << _decompressedData.size() << '\n');
}

void Decompressor::writeBlockToBuffer(const std::vector<uint8_t> &serialized, int x, int y,
                                      ScanDirection dir)
{
    int BLOCK_SIZE = _adaptive ? 16 : _width;

    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        for (int j = 0; j < BLOCK_SIZE; ++j)
        {
            int srcIndex =
                (dir == ScanDirection::Horizontal) ? (i * BLOCK_SIZE + j) : (j * BLOCK_SIZE + i);

            int dstX = x + j;
            int dstY = y + i;
            int dstIndex = dstY * _width + dstX;

            _decompressedData[dstIndex] = serialized[srcIndex];
        }
    }
}

std::vector<uint8_t> Decompressor::decompressLZ77(const std::vector<compressor::LZ77Token> &tokens,
                                                  std::size_t expectedSize)
{
    std::vector<uint8_t> output;

    for (const auto &token : tokens)
    {
        // DEBUG_LOG("Token: " << (int)token.offset << ", " << (int)token.length << ", "
        //      << (int)token.next << endl);
        if (token.offset == 0 || token.length == 0) // no match
        {
            output.push_back(token.next);
            continue;
        }

        size_t start = output.size() - token.offset;
        for (int i = 0; i < token.length; ++i)
        {
            output.push_back(output[start + i]);
        }
        output.push_back(token.next);
    }
    if (output.size() > expectedSize)
    {
        // std::cerr << "Warning: Decompressed output exceeded expected size. Truncating.\n";
        output.resize(expectedSize);
    }

    return output;
}

bool Decompressor::getFlagBit(const vector<uint8_t> &flags, int index)
{
    return (flags[index / 8] >> (7 - (index % 8))) & 1;
}

std::vector<uint8_t> Decompressor::getDecompressedData() { return _decompressedData; }