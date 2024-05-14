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

#include "stdlib.h"

bool is_inside_figure(singleton *s, int y, int x) {
  bool res = false;
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if ((s->figure.current_figure[i][j]) && ((s->figure.y + i) == y) &&
          ((s->figure.x + j) == x)) {
        res = true;
      }
    }
  }

  return res;
}

bool can_move_right(singleton *s) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = TETROMINO_SIZE; j > 0; j--) {
      if (s->figure.current_figure[i][j]) {
        if (s->figure.x + j > WIDTH - 2) {
          res = false;
        } else if (s->game_info->field[s->figure.y + i][s->figure.x + j + 1] &&
                   !is_inside_figure(s, s->figure.y + i, s->figure.x + j + 1)) {
          res = false;
        }
      }
    }
  }

  return res;
}

bool can_rotate(singleton *s) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.rotated_figure[i][j]) {
        int new_x = s->figure.x + j;
        int new_y = s->figure.y + i;

        if (new_x < 0 || new_x >= WIDTH || s->game_info->field[new_x][new_y]) {
          res = false;
        }
      }
    }
  }

  return res;
}

bool can_move_left(singleton *s) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.current_figure[i][j]) {
        if (s->figure.x + j < 1) {
          res = false;
        } else if ((s->game_info
                        ->field[s->figure.y + i][s->figure.x + j - 1]) &&
                   !is_inside_figure(s, s->figure.y + i, s->figure.x + j - 1)) {
          res = false;
        }
      }
    }
  }
  return res;
}

bool can_move_down(singleton *s) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.current_figure[i][j]) {
        if (s->figure.y + i >= HEIGHT - 1) {
          res = false;
        } else if (s->game_info->field[s->figure.y + i + 1][s->figure.x + j] &&
                   !is_inside_figure(s, s->figure.y + i + 1, s->figure.x + j)) {
          res = false;
        }
      }
    }
  }

  return res;
}