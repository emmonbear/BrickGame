/**
 * @file init.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_INIT_H
#define MODULES_INIT_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/common_module.h"

/// @brief Path to the file with high_score
#define PATH "/brick_game/tetris/max_score.txt"

/**
 * @brief Macro that prints an error message and exits the program with a
 * non-zero status code
 *
 * @details
 *
 * This macro is used to handle errors that occur during memory allocation. It
 * prints an error message to the standard error stream and then exits the
 * program with a non-zero status code.
 *
 */
#define MEM_ALLOC_ERROR                         \
  fprintf(stderr, "Memory allocation error\n"); \
  exit(1);

/**
 * @brief Initializes the game's state and allocates memory for the game's data
 * structures.
 *
 * @details
 *
 * This function sets the locale according to the current system settings,
 * initializes the pseudorandom number generator with the current time, and
 * allocates memory for the game's data structures, including the game field,
 * the next tetromino, and the current tetromino. If any memory allocation
 * fails, the function prints an error message and exits the program with a
 * non-zero status code.
 * @param[in,out] s A pointer to the singleton that contains the game's state
 * and information
 */
void init_game(singleton *s);

/**
 * @brief Deallocates memory for the game's data structures and cleans up the
 * game's state.
 *
 * @details
 *
 * This function deallocates memory for the game's data structures, including
 * the game field, the next tetromino, and the current tetromino. It also sets
 * the corresponding pointers to NULL to avoid dangling pointers. If the
 * singleton or any of its data members are not initialized, the function does
 * nothing.
 *
 * @param[in,out] s A pointer to the singleton that contains the game's state
 * and information
 */
void destroy_game(singleton *s);

/**
 * @brief Resets the game's information to its initial state.
 *
 * @details
 *
 * This function sets the game's score, high score, level, speed, and pause flag
 * to their initial values. It also sets the next tetromino's color and type,
 * and the current tetromino's color and type to their initial values. Finally,
 * it sets the game over flag to 0.
 *
 * @param[in,out] s A pointer to the singleton that contains the game's state
 * and information
 */
void reset_game_info(singleton *s);

/**
 * @brief Writes the high score to a file.
 *
 * @details
 *
 * This function gets the current working directory and appends the file path to
 * it. It then opens the file in write mode and writes the high score to it. If
 * the file is not opened, the function does nothing.
 *
 * @param[in,out] s A pointer to the singleton that contains the game's state
 * and information
 */
void write_high_score(singleton *s);

#endif  // MODULES_INIT_H