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

#include "./common.h"

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

void init_game(Game_t *s);
void destroy_game(Game_t *s);
void reset_game_info(Game_t *s);
void write_high_score(Game_t *s);

#endif  // MODULES_INIT_H