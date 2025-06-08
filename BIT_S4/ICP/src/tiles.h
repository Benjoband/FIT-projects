/**
 * @file tiles.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Header file with enum for map reprezentation of tiles
 * @version 1.0
 * @date 2023-05-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef TILES_H
#define TILES_H

/**
 * @brief Enum for map reprezentation of tiles
 * 
 */
enum Tiles : char { PLAYER = 'P', GHOST = 'G', WALL = 'X', KEY = 'K', START = 'S', TARGET = 'T', FLOOR = '.' };

#endif // TILES_H
