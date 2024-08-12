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

static void clear_next(Model_t *model);
static void set_figure_position(figure_t *figure);
static void update_next_figure(Model_t *model, type_t type);

/**
 * @brief Generates a random tetromino type different from the current one.
 *
 * @details
 *
 * This function generates a random tetromino type by selecting a value within
 * the range of possible tetromino types. It ensures that the newly generated
 * tetromino type is different from the current type to provide variety in
 * gameplay. The function loops until a different type is obtained.
 *
 * @param current_type The type of the currently active tetromino.
 * @return A random tetromino type different from the current type.
 */
type_t generate_random(type_t current_type) {
  type_t tmp;
  do {
    tmp = (type_t)(rand() % NUM_TETROMINOS);
  } while (tmp == current_type);

  return tmp;
}

static void set_figure_position(figure_t *figure) {
  figure->x = 3;
  figure->y = 0;
}

static void clear_next(Model_t *model) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->game_info.next[i][j] = 0;
    }
  }
}

/**
 * @brief Copies the next tetromino figure to the current figure.
 *
 * @details
 *
 * This function transfers the tetromino figure data from the "next" field to
 * the "current" field in the game model. It updates the shape, color, and type
 * of the current figure to match the next figure, effectively making the next
 * figure the current one. This process prepares the new figure for placement on
 * the game board.
 *
 * @param model A pointer to the game model containing the next figure and
 * current figure data.
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

static void update_next_figure(Model_t *model, type_t type) {
  switch (type) {
    case TET_I:
      model->game_info.next[0][0] = model->figure.next_color;
      model->game_info.next[0][1] = model->figure.next_color;
      model->game_info.next[0][2] = model->figure.next_color;
      model->game_info.next[0][3] = model->figure.next_color;

      break;

    case TET_Z:
      model->game_info.next[0][0] = model->figure.next_color;
      model->game_info.next[0][1] = model->figure.next_color;
      model->game_info.next[1][1] = model->figure.next_color;
      model->game_info.next[1][2] = model->figure.next_color;

      break;

    case TET_S:
      model->game_info.next[1][0] = model->figure.next_color;
      model->game_info.next[1][1] = model->figure.next_color;
      model->game_info.next[0][1] = model->figure.next_color;
      model->game_info.next[0][2] = model->figure.next_color;

      break;

    case TET_T:
      model->game_info.next[0][0] = model->figure.next_color;
      model->game_info.next[0][1] = model->figure.next_color;
      model->game_info.next[0][2] = model->figure.next_color;
      model->game_info.next[1][1] = model->figure.next_color;

      break;

    case TET_L:
      model->game_info.next[0][0] = model->figure.next_color;
      model->game_info.next[0][1] = model->figure.next_color;
      model->game_info.next[0][2] = model->figure.next_color;
      model->game_info.next[1][0] = model->figure.next_color;

      break;

    case TET_J:
      model->game_info.next[0][0] = model->figure.next_color;
      model->game_info.next[1][0] = model->figure.next_color;
      model->game_info.next[1][1] = model->figure.next_color;
      model->game_info.next[1][2] = model->figure.next_color;

      break;

    case TET_O:
      model->game_info.next[0][0] = model->figure.next_color;
      model->game_info.next[0][1] = model->figure.next_color;
      model->game_info.next[1][0] = model->figure.next_color;
      model->game_info.next[1][1] = model->figure.next_color;

      break;
    case NONE:
      break;
  }
}

/**
 * @brief Generates a new tetromino figure and updates the model.
 *
 * @details
 *
 * This function prepares the game model with a new tetromino figure by
 * performing the following steps:
 * 1. Clears the data of the next figure to prepare for a new figure.
 * 2. Sets the color of the new figure based on its type.
 * 3. Initializes the position of the new figure on the game board.
 * 4. Updates the "next" figure data to reflect the new tetromino type.
 *
 * @param model A pointer to the game model where the new figure will be set up.
 */
void generate_new_figure(Model_t *model) {
  clear_next(model);

  model->figure.next_color = model->figure.next_type + 1;

  set_figure_position(&model->figure);

  update_next_figure(model, model->figure.next_type);
}
