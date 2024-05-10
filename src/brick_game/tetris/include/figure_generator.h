/**
 * @file figure_generator.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_FIGURE_GENERATOR
#define MODULES_FIGURE_GENERATOR

#include "../include/common.h"

/// @brief Amount of tetrominoes
#define NUM_TETROMINOS 7

/// @brief Number of positions
#define NUM_POSITIONS 5

/// @brief The size of the tetromino
#define TETROMINO_SIZE 4

figure_t generate_new_figure(void);

#endif  // MODULES_FIGURE_GENERATOR