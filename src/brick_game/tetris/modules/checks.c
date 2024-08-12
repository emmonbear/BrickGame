/**
 * @file checks.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/checks.h"

#include "../include/operations.h"
#include "stdlib.h"

static void get_score(int lines, Model_t *model);
static void update_level(Model_t *model);

bool is_inside_figure(Model_t *model, int y, int x) {
  bool res = false;
  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      if ((model->figure.current_figure[i][j]) &&
          ((model->figure.y + i) == y) && ((model->figure.x + j) == x)) {
        res = true;
      }
    }
  }

  return res;
}

bool can_move_right(Model_t *model) {
  bool res = true;

  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = TETROMINO_SIZE - 1; j > 0; j--) {
      if (model->figure.current_figure[i][j]) {
        if (model->figure.x + j > WIDTH - 2) {
          res = false;
          break;
        } else if (model->game_info
                       .field[model->figure.y + i][model->figure.x + j + 1] &&
                   !is_inside_figure(model, model->figure.y + i,
                                     model->figure.x + j + 1)) {
          res = false;
        }
      }
    }
  }

  return res;
}

bool can_move_left(Model_t *model) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (model->figure.current_figure[i][j]) {
        if (model->figure.x + j < 1) {
          res = false;
        } else if ((model->game_info
                        .field[model->figure.y + i][model->figure.x + j - 1]) &&
                   !is_inside_figure(model, model->figure.y + i,
                                     model->figure.x + j - 1)) {
          res = false;
        }
      }
    }
  }

  return res;
}

bool can_rotate(Model_t *model) {
  bool res = true;

  remove_figure(model);
  for (size_t i = 0; i < TETROMINO_SIZE && res; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE && res; j++) {
      if (model->figure.rotated_figure[i][j]) {
        int new_x = model->figure.x + j;
        int new_y = model->figure.y + i;

        if ((new_x < 0 || new_x >= WIDTH ||
             model->game_info.field[new_y][new_x])) {
          res = false;
          put_figure(model);
        }
      }
    }
  }

  return res;
}

bool can_move_down(Model_t *model) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (model->figure.current_figure[i][j]) {
        if (model->figure.y + i >= HEIGHT - 1) {
          res = false;
        } else if (model->game_info
                       .field[model->figure.y + i + 1][model->figure.x + j] &&
                   !is_inside_figure(model, model->figure.y + i + 1,
                                     model->figure.x + j)) {
          res = false;
        }
      }
    }
  }

  return res;
}

void check_full_lines(Model_t *model) {
  int full_lines = 0;

  for (size_t i = 0; i < HEIGHT; i++) {
    int filled = 1;
    for (size_t j = 0; (j < WIDTH) && (filled != 0); j++) {
      if (!model->game_info.field[i][j]) {
        filled = 0;
      }
    }
    if (filled) {
      for (size_t k = i; k > 0; k--) {
        for (size_t l = 0; l < WIDTH; l++) {
          model->game_info.field[k][l] = model->game_info.field[k - 1][l];
        }
      }
      full_lines++;
      i--;
    }
  }
  get_score(full_lines, model);
  update_level(model);
}

static void get_score(int lines, Model_t *model) {
  int score = 0;

  switch (lines) {
    case 1:
      score = 100;
      break;

    case 2:
      score = 300;
      break;

    case 3:
      score = 700;
      break;

    case 4:
      score = 1500;
      break;
  }

  model->game_info.score += score;

  if (model->game_info.high_score < model->game_info.score) {
    model->game_info.high_score = model->game_info.score;
  }
}

static void update_level(Model_t *model) {
  while (model->game_info.score >= SCORE_PER_LEVEL * (model->game_info.level)) {
    if (model->game_info.level < MAX_LEVEL) {
      model->game_info.level++;
    } else {
      break;
    }
  }
}

bool can_put_new_line(Model_t *model) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE && res; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE && res; j++) {
      if (model->game_info.next[i][j] &&
          model->game_info.field[i + model->figure.y][j + model->figure.x]) {
        res = false;
      }
    }
  }

  return res;
}
