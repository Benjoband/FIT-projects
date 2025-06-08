/**
 * @file model.cpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Implementation of the model functions, just neighbours difference.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "model.hpp"

using namespace std;

namespace model
{

void applyModel(std::vector<uint8_t> &data)
{
    for (std::size_t i = data.size() - 1; i >= 1; --i)
    {
        data[i] = static_cast<uint8_t>((256 + data[i] - data[i - 1]) % 256);
    }
}

void undoModel(std::vector<uint8_t> &data)
{
    for (std::size_t i = 1; i < data.size(); ++i)
    {
        data[i] = static_cast<uint8_t>((data[i] + data[i - 1]) % 256);
    }
}
} // namespace model