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

#include "./common.h"

/// @brief Amount of tetrominoes
#define NUM_TETROMINOS 7

/// @brief Number of positions
#define NUM_POSITIONS 5

void generate_new_figure(Game_t *s);
void copy_next_to_current(Game_t *s);

#endif  // MODULES_FIGURE_GENERATOR