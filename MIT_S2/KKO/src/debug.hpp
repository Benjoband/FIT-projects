/**
 * @file debug.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Macro for debugging
 * @version 1.0
 * @date 2025-05-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>

#ifdef ENABLE_DEBUG
#define DEBUG_LOG(x) std::cerr << x
#else
#define DEBUG_LOG(x)
#endif