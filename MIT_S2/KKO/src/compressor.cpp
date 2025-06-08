/**
 * @file compressor.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of LZ77 compression algorithm
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "compressor.hpp"

using namespace std;

LZ77Compressor::LZ77Compressor()
    : buffer_size(compressor::SEARCH_BUFF), lookahead_size(compressor::LOOKAHEAD_BUFF)
{
}

compressor::CompressedBlock LZ77Compressor::compress(const Block &block, vector<uint8_t> &data)
{
    compressor::CompressedBlock compressedBlock = createCompressedBlock(block);

    size_t pos = 0;
    while (pos < data.size())
    {
        int best_offset = 0;
        int best_length = 0;

        int search_start = (pos >= compressor::SEARCH_BUFF) ? pos - compressor::SEARCH_BUFF : 0;
        int max_match_len =
            min(static_cast<int>(compressor::LOOKAHEAD_BUFF), static_cast<int>(data.size() - pos));

        // Find the best match in search buffer
        for (int i = search_start; i < static_cast<int>(pos); ++i)
        {
            int length = 0;
            while (length < max_match_len && data[i + length] == data[pos + length])
            {
                ++length;
            }

            if (length > best_length)
            {
                best_offset = pos - i;
                best_length = length;
            }
        }

        uint8_t next = (pos + best_length < data.size()) ? data[pos + best_length] : 0;
        compressedBlock.tokens.push_back(
            {static_cast<uint16_t>(best_offset), static_cast<uint8_t>(best_length), next});
        pos += best_length + 1;
    }

    // now control size of the compressed block
    if (compressedBlock.tokens.size() * sizeof(compressor::LZ77Token) >
        data.size()) // bigger than original
    {
        compressedBlock.compressed = false;
        compressedBlock.data = data;
        compressedBlock.tokens.clear();
    }
    else // smaller than original
    {
        compressedBlock.compressed = true;
        compressedBlock.data.clear();
    }
    return compressedBlock;
}

compressor::CompressedBlock LZ77Compressor::createCompressedBlock(const Block &block)
{
    compressor::CompressedBlock compressedBlock;
    compressedBlock.x = block.x;
    compressedBlock.y = block.y;
    compressedBlock.width = block.width;
    compressedBlock.height = block.height;
    compressedBlock.scan_direction = block.scan_direction;
    return compressedBlock;
}
