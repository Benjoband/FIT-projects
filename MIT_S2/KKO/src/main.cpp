/**
 * @file main.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Runs the main program for LZ77 compression and decompression.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <iostream>
#include <string>

#include "arguments.hpp"
#include "compressor.hpp"
#include "debug.hpp"
#include "decompressor.hpp"
#include "fileio.hpp"
#include "model.hpp"
#include "scanner.hpp"

using namespace std;

int run(Arguments &args)
{
    try
    {
        FileIO fileIO(args);
        if (args.isCompress()) // COMPRESSING
        {
            vector<uint8_t> data = fileIO.readFile();

            std::vector<Block> blocks = scanner::createBlocks(data, args);

            std::vector<compressor::CompressedBlock> compressedBlocks;
            LZ77Compressor compressor;

            for (const auto &block : blocks)
            {
                // Horizontal
                std::vector<uint8_t> horizontal =
                    scanner::serializeBlock(block, ScanDirection::Horizontal);
                if (args.isModel())
                {
                    model::applyModel(horizontal);
                }
                compressor::CompressedBlock compressedH = compressor.compress(block, horizontal);
                compressedH.scan_direction = ScanDirection::Horizontal;

                // Vertical
                std::vector<uint8_t> vertical =
                    scanner::serializeBlock(block, ScanDirection::Vertical);
                if (args.isModel())
                {
                    DEBUG_LOG("Applying model: " << args.isModel());
                    model::applyModel(vertical);
                }
                compressor::CompressedBlock compressedV = compressor.compress(block, vertical);
                compressedV.scan_direction = ScanDirection::Vertical;

                if (compressedH.compressed && compressedV.compressed) // Compare compressed blocks
                {
                    if (compressedH.tokens.size() <= compressedV.tokens.size())
                    {
                        compressedBlocks.push_back(std::move(compressedH));
                    }
                    else
                    {
                        compressedBlocks.push_back(std::move(compressedV));
                    }
                }
                else if (compressedH.compressed) // Only horizontal compressed
                    compressedBlocks.push_back(std::move(compressedH));
                else if (compressedV.compressed) // Only vertical compressed
                    compressedBlocks.push_back(std::move(compressedV));
                else // Both uncompressed
                {
                    // Both uncompressed, choose one (horizontal by default)
                    compressedH.scan_direction = ScanDirection::Horizontal;
                    compressedBlocks.push_back(std::move(compressedH));
                }
            }
            fileIO.writeCompressedFile(compressedBlocks);
        }
        else // DECOMPRESSING
        {
            FileIO fileIO(args);
            Decompressor decompressor(args);
            try
            {
                decompressor.decompressBlocks();
                vector<uint8_t> decompressedData = decompressor.getDecompressedData();
                fileIO.writeDecompressedFile(decompressedData);
            }
            catch (const std::exception &e)
            {
                cerr << "Error: " << e.what() << endl;
                return 1; // Return error
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1; // Return error
    }

    return 0; // Return success
}

int main(int argc, char *argv[])
{
    Arguments args(argc, argv);
    return run(args);
}