/**
 * @file scanner.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of the scanner module, with functions to create blocks and serialise data
 * from images.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "scanner.hpp"

using namespace std;

namespace scanner
{

std::vector<Block> createBlocks(const std::vector<std::uint8_t> &data, const Arguments &args)
{
    const std::size_t width = args.getWidth();

    if (args.isAdaptive())
    {
        return scanner::divideIntoBlocks(data, width);
    }
    else
    {
        Block oneBlock = scanner::createOneImageblock(data, width);
        return {oneBlock}; // wrap into vector for uniform processing
    }
}

Block createOneImageblock(const std::vector<std::uint8_t> &image_data, std::size_t image_width)
{
    std::size_t total_pixels = image_data.size();
    std::size_t image_height = total_pixels / image_width;

    Block block;
    block.x = 0;
    block.y = 0;
    block.width = image_width;
    block.height = image_height;
    block.scan_direction = ScanDirection::Horizontal;
    block.image_data = &image_data;
    block.image_width = image_width;
    return block;
}

std::vector<Block> divideIntoBlocks(const std::vector<std::uint8_t> &image_data,
                                    std::size_t image_width)
{
    std::size_t total_pixels = image_data.size();
    std::size_t image_height = total_pixels / image_width;

    std::vector<Block> blocks;

    for (std::size_t y = 0; y < image_height; y += scanner::BLOCK_SIZE)
    {
        for (std::size_t x = 0; x < image_width; x += scanner::BLOCK_SIZE)
        {
            Block block;
            block.x = x;
            block.y = y;
            block.width = std::min(static_cast<std::size_t>(scanner::BLOCK_SIZE), image_width - x);
            block.height =
                std::min(static_cast<std::size_t>(scanner::BLOCK_SIZE), image_height - y);
            block.scan_direction = ScanDirection::Horizontal; // default, will optimize later
            block.image_data = &image_data;
            block.image_width = image_width;
            blocks.push_back(block);
        }
    }

    return blocks;
}

std::vector<std::uint8_t> serializeBlock(const Block &block, ScanDirection direction)
{
    std::vector<std::uint8_t> result;
    result.reserve(block.width * block.height);

    switch (direction)
    {
    case ScanDirection::Horizontal:
        for (std::size_t row = 0; row < block.height; ++row)
        {
            for (std::size_t col = 0; col < block.width; ++col)
            {
                result.push_back(block.get_pixel(row, col));
            }
        }
        break;

    case ScanDirection::Vertical:
        for (std::size_t col = 0; col < block.width; ++col)
        {
            for (std::size_t row = 0; row < block.height; ++row)
            {
                result.push_back(block.get_pixel(row, col));
            }
        }
        break;

    default:
        throw std::runtime_error("Unknown scan direction in serialize_block");
    }

    return result;
}
} // namespace scanner