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

void generate_new_figure(Model_t *model) {
  clear_next(model);

  model->figure.next_color = model->figure.next_type + 1;

  set_figure_position(&model->figure);

  update_next_figure(model, model->figure.next_type);
}
