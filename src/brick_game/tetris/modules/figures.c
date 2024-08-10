/**
 * @file figure_generator.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/figures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void clear_next(Model_t *model) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->game_info.next[i][j] = 0;
    }
  }
}

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
 * @param[in, out] s - A pointer to the Model_t object that contains the
 * game's state and information.
 */
void copy_next_to_current(Model_t *model) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->figure.current_figure[i][j] = model->game_info.next[i][j];
    }
  }
  model->figure.current_color = model->figure.next_color;
  model->figure.current_type = model->figure.next_type;
}

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
 * @param[in, out] s - A pointer to the Model_t object that contains the
 * game's state and information.
 */
void generate_new_figure(Model_t *model) {
  clear_next(model);

  size_t tmp;
  do {
    tmp = rand() % NUM_TETROMINOS;
  } while (tmp == model->figure.current_type);

  model->figure.next_color = tmp + 1;
  model->figure.next_type = tmp;
  model->figure.x = 3;
  model->figure.y = 0;

  switch (model->figure.next_type) {
    case TET_I:
      model->game_info.next[0][0] = model->game_info.next[0][1] =
          model->game_info.next[0][2] = model->game_info.next[0][3] =
              model->figure.next_color;
      break;

    case TET_Z:
      model->game_info.next[0][0] = model->game_info.next[0][1] =
          model->game_info.next[1][1] = model->game_info.next[1][2] =
              model->figure.next_color;
      break;

    case TET_S:
      model->game_info.next[1][0] = model->game_info.next[1][1] =
          model->game_info.next[0][1] = model->game_info.next[0][2] =
              model->figure.next_color;
      break;

    case TET_T:
      model->game_info.next[0][0] = model->game_info.next[0][1] =
          model->game_info.next[0][2] = model->game_info.next[1][1] =
              model->figure.next_color;
      break;

    case TET_L:
      model->game_info.next[0][0] = model->game_info.next[0][1] =
          model->game_info.next[0][2] = model->game_info.next[1][0] =
              model->figure.next_color;
      break;

    case TET_J:
      model->game_info.next[0][0] = model->game_info.next[1][0] =
          model->game_info.next[1][1] = model->game_info.next[1][2] =
              model->figure.next_color;
      break;

    case TET_O:
      model->game_info.next[0][0] = model->game_info.next[0][1] =
          model->game_info.next[1][0] = model->game_info.next[1][1] =
              model->figure.next_color;
      break;
  }
}
