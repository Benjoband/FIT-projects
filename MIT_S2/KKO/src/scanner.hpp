/**
 * @file scanner.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for the scanner module.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "arguments.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

/**
 * @brief Enum class for scan direction. Supports horizontal and vertical scan.
 *
 */
enum class ScanDirection : uint8_t
{
    Horizontal,
    Vertical
};

/**
 * @brief Struct for a block of pixels. Contains the coordinates, size, and scan direction.
 *
 */
struct Block
{
        std::size_t x;
        std::size_t y;
        std::size_t width;
        std::size_t height;
        ScanDirection scan_direction;

        const std::vector<std::uint8_t> *image_data;
        std::size_t image_width;

        std::uint8_t get_pixel(std::size_t row, std::size_t col) const
        {
            return (*image_data)[(y + row) * image_width + (x + col)];
        }
};

namespace scanner
{

/**
 * @brief Block size in bytes. The block size is 16x16 pixels, so the size is 16 * 16 = 256 bytes.
 *
 */
const uint8_t BLOCK_SIZE = 16;

/**
 * @brief Create blocks from the image data.
 *
 * @param data
 * @param args
 * @return std::vector<Block>
 */
std::vector<Block> createBlocks(const std::vector<uint8_t> &data, const Arguments &args);

/**
 * @brief Create a block with width as a whole picture.
 *
 * @param image_data
 * @param image_width
 * @return Block
 */
Block createOneImageblock(const std::vector<std::uint8_t> &image_data, std::size_t image_width);

/**
 * @brief For adaptive compression, divide the image into blocks of size block_size.
 *
 * @param image_data
 * @param image_width
 * @param block_size
 * @return * std::vector<Block>
 */
std::vector<Block> divideIntoBlocks(const std::vector<std::uint8_t> &image_data,
                                    std::size_t image_width);

/**
 * @brief Returns a vector of uint8_t that represents the serialized block.
 *
 * @param block
 * @return std::vector<uint8_t>
 */
std::vector<uint8_t> serializeBlock(const Block &block, ScanDirection direction);

} // namespace scanner

#endif // SCANNER_HPP