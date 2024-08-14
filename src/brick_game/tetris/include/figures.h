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

#include "./model.h"

/// @brief Amount of tetrominoes
#define NUM_TETROMINOS 7

/// @brief Number of positions
#define NUM_POSITIONS 5

void generate_new_figure(Model_t *model);
void copy_next_to_current(Model_t *model);
type_t generate_random(type_t current_type);
void set_figure_position(figure_t *figure);

#endif  // MODULES_FIGURE_GENERATOR
