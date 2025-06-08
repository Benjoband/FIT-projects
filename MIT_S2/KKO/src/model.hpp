/**
 * @file model.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file for the model functions, just neighbours difference.
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>
#include <iostream>
#include <vector>

namespace model
{
/**
 * @brief Apply difference of neighbours pixel to the data.
 *
 * @param data
 */
void applyModel(std::vector<std::uint8_t> &data);

/**
 * @brief Apply inverse model to the data.
 *
 * @param data
 */
void undoModel(std::vector<std::uint8_t> &data);

} // namespace model

#endif // MODEL_HPP