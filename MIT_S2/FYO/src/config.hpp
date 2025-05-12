/**
 * @file config.hpp
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Default values used for the start of the simulation
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef CONFIG_HPP
#define CONFIG_HPP

/**
 * @brief Namespace for default values used for the start of the simulation
 *
 */
namespace config
{
// Window properties
static const unsigned int SCREEN_WIDTH = 1920;
static const unsigned int SCREEN_HEIGHT = 1080;
static const unsigned int FPS = 30;

// Laser properties
static const unsigned int LASER_WIDTH = 150;
static const unsigned int LASER_HEIGHT = 50;
static const unsigned int LASER_X = 150;
static const unsigned int LASER_Y = SCREEN_HEIGHT / 2;

// Ray properties
static const unsigned int RAY_WIDTH = 2222; // pythagoras for 1920x1080
static const unsigned int RAY_HEIGHT = 2;

// Fiber properties

static const unsigned int CABLE_START_X = SCREEN_WIDTH / 5;
static const unsigned int CABLE_END_X = SCREEN_WIDTH;
static const unsigned int CABLE_WIDTH = SCREEN_WIDTH - CABLE_START_X;
static const unsigned int CABLE_HEIGHT = 200;

static const unsigned int CORE_WIDTH = CABLE_WIDTH;
static const unsigned int CORE_HEIGHT = 200;
static const unsigned int CORE_X = CABLE_START_X;
static const unsigned int CORE_Y = SCREEN_HEIGHT / 2 - CORE_HEIGHT / 2;

static const unsigned int CORE_STEP_INDEX_HEIGHT = 200;
static const unsigned int CORE_GRADED_INDEX_HEIGHT = 128;
static const unsigned int CORE_SINGLE_MODE_HEIGHT = 20;

static const unsigned int CLADDING_WIDTH = CABLE_WIDTH;

static const unsigned int CLADDING_STEP_INDEX_HEIGHT = 10;
static const unsigned int CLADDING_GRADED_INDEX_HEIGHT = 46;
static const unsigned int CLADDING_SINGLE_MODE_HEIGHT = 100;

static const unsigned int CLADDING_X = CABLE_START_X; // TODO

static const unsigned int CLADDING_STEP_TOP_Y =
    SCREEN_HEIGHT / 2 - CORE_STEP_INDEX_HEIGHT / 2 - CLADDING_STEP_INDEX_HEIGHT;
static const unsigned int CLADDING_STEP_BOT_Y = SCREEN_HEIGHT / 2 + CORE_STEP_INDEX_HEIGHT / 2;

static const unsigned int CLADDING_GRADED_TOP_Y =
    SCREEN_HEIGHT / 2 - CORE_GRADED_INDEX_HEIGHT / 2 - CLADDING_GRADED_INDEX_HEIGHT;
static const unsigned int CLADDING_GRADED_BOT_Y = SCREEN_HEIGHT / 2 + CORE_GRADED_INDEX_HEIGHT / 2;

static const unsigned int CLADDING_SINGLE_TOP_Y =
    SCREEN_HEIGHT / 2 - CORE_SINGLE_MODE_HEIGHT / 2 - CLADDING_SINGLE_MODE_HEIGHT;
static const unsigned int CLADDING_SINGLE_BOT_Y = SCREEN_HEIGHT / 2 + CORE_SINGLE_MODE_HEIGHT / 2;

static const unsigned int GRADED_INDEX_N = 8;

static const unsigned int GRADED_INDEX_Y[10] = {
    476, // Cladding 100% refractive index
    492, // Layer 0 - outermost
    508, // Layer 1
    524, // Layer 2
    540, // Layer 3 - near center
    540, // Layer 4 - near center (symmetric)
    556, // Layer 5
    572, // Layer 6
    588, // Layer 7 - outermost
    604  // Cladding 100% refractive index
};
static constexpr float GRADED_INDEX_REFRACTION[10] = {
    1,   // cladding
    1.1, // outermost
    1.3, 1.5,
    1.7, // near center
    1.7, // near center
    1.5, 1.3,
    1.1, // outermost
    1    // cladding
};
}; // namespace config

#endif // CONFIG_HPP