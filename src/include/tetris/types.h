/**
 * @file types.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_TETRIS_TYPES_H_
#define SRC_INCLUDE_TETRIS_TYPES_H_

#include <stdbool.h>

#include "../common/common.h"
#include "../common/game_info.h"

#define TETROMINO_SIZE 4
#define NUM_STAGES 7
#define MAX_LEVEL 10
#define SCORE_PER_LEVEL 600

typedef enum {
  TET_I,
  TET_Z,
  TET_S,
  TET_T,
  TET_L,
  TET_J,
  TET_O,
  NONE,
} type_t;

typedef struct {
  type_t next_type;      ///< The type of the next tetromino figure.
  type_t current_type;   ///< The type of the current tetromino figure.
  int x, y;              ///< The x and y coordinates of the top left corner of
                         ///< the current tetromino figure on the game board.
  int next_color;        ///< The color index of the next tetromino figure.
  int current_color;     ///< The color index of the current tetromino figure.
  int **current_figure;  ///< A 2D array representing the shape of the current
                         ///< tetromino figure.
  int **rotated_figure;  ///< A 2D array representing the shape of the current
                         ///< tetromino figure after rotation.
} figure_t;

typedef struct {
  figure_t figure;  ///< Information about figures
  int timer;        ///< The game timer for managing game speed or intervals
  bool game_over;   ///< Flag indicating whether the game is over
  stage_t stage;    ///< The current stage or level of the game
} Model_t;

#endif  // SRC_INCLUDE_TETRIS_TYPES_H_
