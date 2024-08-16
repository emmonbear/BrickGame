/**
 * @file common.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_COMMON_INCLUDE_COMMON_H_
#define SRC_COMMON_INCLUDE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **field;  ///< 2D array representing the game field, where each element
                ///< corresponds to a cell on the field. The value of an element
                ///< is either 0 (empty cell) or a positive integer (cell
                ///< occupied by a block, with the value indicating the color of
                ///< the block).
  int **next;   ///< 2D array representing the next block to be spawned.
  int score;    ///< The current score of the player.
  int high_score;  ///< The highest score achieved by any player.
  int level;  ///< The current level of the game, which determines the speed at
              ///< which blocks fall.
  int speed;  ///< The speed at which blocks fall, measured in milliseconds
              ///< between each downward movement.
  int pause;  ///< A flag indicating whether the game is currently paused (1) or
              ///< not (0).
} GameInfo_t;

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
  exit(1)

void allocate_2d_array(int ***array, size_t rows, size_t cols);
void destroy_2d_array(int ***array, size_t rows);

#endif  // SRC_COMMON_INCLUDE_COMMON_H_
