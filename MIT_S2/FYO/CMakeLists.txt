cmake_minimum_required(VERSION 3.28)
project(FiberOpticsSimulation LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Collect all source files
set(SOURCES
    src/main.cpp
    src/laser.cpp
    src/ray.cpp
    src/fiber.cpp
    src/core.cpp
    src/textui.cpp
)

# Collect all header files (not strictly required, but useful for IDEs)
set(HEADERS
    src/ray.hpp
    src/laser.hpp
    src/config.hpp
    src/fiber.hpp
    src/core.hpp
    src/ray.hpp
    src/textui.hpp
)

# Create the executable
add_executable(fiber_sim ${SOURCES} ${HEADERS})

# Set C++ standard
target_compile_features(fiber_sim PRIVATE cxx_std_17)

# Link SFML
target_link_libraries(fiber_sim PRIVATE SFML::Graphics)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()