/**
 * @file figures.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../include/tetris/figures.h"

#define NUM_TETROMINOS 7

static void clear_next(GameInfo_t *game_info);
static void update_next_figure(Model_t *model, GameInfo_t *game_info,
                               type_t type);

type_t generate_random(type_t current_type) {
  type_t tmp;
  do {
    tmp = (type_t)(rand() % NUM_TETROMINOS);
  } while (tmp == current_type);

  return tmp;
}

void set_start_position(figure_t *figure) {
  figure->x = 3;
  figure->y = 0;
}

void generate_new_figure(Model_t *model, GameInfo_t *game_info) {
  clear_next(game_info);

  model->figure.next_color = model->figure.next_type + 1;

  set_start_position(&model->figure);

  update_next_figure(model, game_info, model->figure.next_type);
}

void copy_next_to_current(Model_t *model, GameInfo_t *game_info) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->figure.current_figure[i][j] = game_info->next[i][j];
    }
  }
  model->figure.current_color = model->figure.next_color;
  model->figure.current_type = model->figure.next_type;
}

static void clear_next(GameInfo_t *game_info) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      game_info->next[i][j] = 0;
    }
  }
}

static void update_next_figure(Model_t *model, GameInfo_t *game_info,
                               type_t type) {
  switch (type) {
    case TET_I:
      game_info->next[0][0] = model->figure.next_color;
      game_info->next[0][1] = model->figure.next_color;
      game_info->next[0][2] = model->figure.next_color;
      game_info->next[0][3] = model->figure.next_color;

      break;

    case TET_Z:
      game_info->next[0][0] = model->figure.next_color;
      game_info->next[0][1] = model->figure.next_color;
      game_info->next[1][1] = model->figure.next_color;
      game_info->next[1][2] = model->figure.next_color;

      break;

    case TET_S:
      game_info->next[1][0] = model->figure.next_color;
      game_info->next[1][1] = model->figure.next_color;
      game_info->next[0][1] = model->figure.next_color;
      game_info->next[0][2] = model->figure.next_color;

      break;

    case TET_T:
      game_info->next[0][0] = model->figure.next_color;
      game_info->next[0][1] = model->figure.next_color;
      game_info->next[0][2] = model->figure.next_color;
      game_info->next[1][1] = model->figure.next_color;

      break;

    case TET_L:
      game_info->next[0][0] = model->figure.next_color;
      game_info->next[0][1] = model->figure.next_color;
      game_info->next[0][2] = model->figure.next_color;
      game_info->next[1][0] = model->figure.next_color;

      break;

    case TET_J:
      game_info->next[0][0] = model->figure.next_color;
      game_info->next[1][0] = model->figure.next_color;
      game_info->next[1][1] = model->figure.next_color;
      game_info->next[1][2] = model->figure.next_color;

      break;

    case TET_O:
      game_info->next[0][0] = model->figure.next_color;
      game_info->next[0][1] = model->figure.next_color;
      game_info->next[1][0] = model->figure.next_color;
      game_info->next[1][1] = model->figure.next_color;

      break;
    case NONE:
      break;
  }
}
