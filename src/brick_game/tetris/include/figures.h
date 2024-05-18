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

#include "../include/common_module.h"

/// @brief Amount of tetrominoes
#define NUM_TETROMINOS 7

/// @brief Number of positions
#define NUM_POSITIONS 5

/**
 * @brief Generates a new tetromino and places it in the "next" position.
 *
 * @details
 *
 * This function first clears the "next" position using the clear_next()
 * function. Then, it generates a random number between 0 and NUM_TETROMINOS - 7
 * (inclusive) using the rand() function. If the generated number is equal to
 * the current tetromino's type, it generates a new number until it is
 * different. The function then sets the "next" tetromino's color and type based
 * on the generated number, and sets its position on the game field using the x
 * and y coordinates of the "next" position.
 *
 * @param[in, out] s - A pointer to the singleton object that contains the
 * game's state and information.
 */
void generate_new_figure(singleton *s);

/**
 * @brief Copies the next tetromino to the current tetromino.
 *
 * @details
 *
 * This function iterates over the cells of the next tetromino using a nested
 * loop and copies each cell to the corresponding cell of the current tetromino.
 * Then, it copies the color and type of the next tetromino to the current
 * tetromino.
 *
 * @param[in, out] s - A pointer to the singleton object that contains the
 * game's state and information.
 */
void copy_next_to_current(singleton *s);

#endif  // MODULES_FIGURE_GENERATOR