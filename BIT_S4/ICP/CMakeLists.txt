cmake_minimum_required(VERSION 3.5)

project(pacman VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Network)


if(UNIX AND NOT APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    find_program(CLANG_TIDY_EXE NAMES clang-tidy clang-tidy-17 clang-tidy-16 clang-tidy-15 DOC "Path to clang-tidy executable")
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE} "--config-file=${CMAKE_CURRENT_LIST_DIR}/.clang-tidy" "-p=build/${CMAKE_BUILD_TYPE}")
    else()
        message(STATUS "clang-tidy not found, it is highly recommended to install it")
    endif()

    find_program(CPPCHECK_EXE NAMES "cppcheck" DOC "Path to cppcheck executable")
    if(CPPCHECK_EXE)
        set(CMAKE_CXX_CPPCHECK "${CPPCHECK_EXE}"
                        "--enable=warning,style,performance,portability,information,missingInclude"
                        "--std=c++17"
                        "--inline-suppr"
                        "--error-exitcode=0"
                        "--template=gcc"
                        "-i{CMAKE_BINARY_DIR}")
    else()
        message(STATUS "cppcheck not found, it is highly recommended to install it")
    endif()
endif()

include_directories(src)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/gamewindow.h
        src/gamewindow.cpp
        src/gamewindow.ui
        src/server.h
        src/server.cpp
        src/map.h
        src/client.cpp
        src/client.h
        src/map.cpp
        src/server_objects/object.h
        src/server_objects/object.cpp
        src/client_controller.h
        src/client_controller.cpp
        src/client_objects/wall.hpp
        src/client_objects/wall.cpp
        src/game.h
        src/game.cpp
        src/dateutils.h
        src/dateutils.cpp
        src/server_objects/player.h
        src/server_objects/player.cpp
        src/server_objects/ghost.h
        src/server_objects/ghost.cpp
        src/server_objects/start.h
        src/server_objects/start.cpp
        src/server_objects/key.h
        src/server_objects/key.cpp
        src/server_objects/target.h
        src/server_objects/target.cpp
        src/communication/message.h
        src/communication/message.cpp
        src/communication/map_message.h
        src/communication/map_message.cpp
        src/communication/score_message.cpp
        src/communication/score_message.h
        src/communication/keys_message.cpp
        src/communication/keys_message.h
        src/communication/direction_message.h
        src/communication/direction_message.cpp
        src/communication/ending_message.h
        src/communication/ending_message.cpp
        src/communication/client_id.h
        src/communication/client_id.cpp
        src/tiles.h
        src/aboutwindow.ui
        src/aboutwindow.cpp
        src/aboutwindow.h
        src/playwindow.h
        src/playwindow.cpp
        src/playwindow.ui
        src/replay.h
        src/replay.cpp
        src/replay.ui
        src/client_objects/floor.cpp
        src/client_objects/floor.hpp
        src/client_objects/ghost.cpp
        src/client_objects/ghost.hpp
        src/client_objects/key.cpp
        src/client_objects/key.hpp
        src/client_objects/pacman.cpp
        src/client_objects/pacman.hpp
        src/client_objects/start.cpp
        src/client_objects/start.hpp
        src/client_objects/target.cpp
        src/client_objects/target.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pacman
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET pacman APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(pacman SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(pacman
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(pacman PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(pacman PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Linux and GCC/CLANG only
if(UNIX AND NOT APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pacman PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(pacman PRIVATE -fsanitize=address -fsanitize=leak)
    target_link_options(pacman PRIVATE -fsanitize=address -fsanitize=leak)
endif()

install(TARGETS pacman
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pacman)
endif()
