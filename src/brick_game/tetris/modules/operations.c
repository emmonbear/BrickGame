/**
 * @file operations.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/operations.h"

#include <stdlib.h>

void put_figure(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.current_figure[i][j]) {
        s->game_info->field[s->figure.y + i][s->figure.x + j] =
            s->figure.current_color;
      }
    }
  }
}

void move_down(singleton *s) {
  remove_figure(s);
  s->figure.y++;
  put_figure(s);
}

void remove_figure(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.current_figure[i][j]) {
        s->game_info->field[s->figure.y + i][s->figure.x + j] = 0;
      }
    }
  }
}

void move_left(singleton *s) {
  if (can_move_left(s)) {
    remove_figure(s);
    s->figure.x--;
    put_figure(s);
  }
}

void move_right(singleton *s) {
  remove_figure(s);
  s->figure.x++;
  put_figure(s);
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

bool can_move_left(singleton *s) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < 1; j++) {
      if (s->figure.current_figure[i][j]) {
        if (s->figure.x + j < 1) {
          res = false;
        } else if (s->game_info->field[s->figure.y + i][s->figure.x + j - 1]) {
          res = false;
        }
      }
    }
  }
  return res;
}

bool is_inside_figure(singleton *s, int y, int x) {
  bool res = false;
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if ((s->figure.current_figure[i][j]) && (s->figure.y + i) == y &&
          (s->figure.x + j) == x) {
        res = true;
      }
    }
  }

  return res;
}
