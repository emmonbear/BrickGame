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

static void reset_position(singleton *s);

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
  if (can_move_right(s)) {
    remove_figure(s);
    s->figure.x++;
    put_figure(s);
  }
}

void rotate_figure(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      s->figure.current_figure[i][j] = s->figure.rotated_figure[i][j];
      s->figure.rotated_figure[i][j] = 0;
    }
  }
  put_figure(s);
}

void get_rotated_figure(singleton *s) {
  // Transpose matrix
  int tmp[TETROMINO_SIZE][TETROMINO_SIZE];
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      tmp[i][j] = s->figure.current_figure[j][i];
    }
  }

  // Reversing columns
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      s->figure.rotated_figure[i][j] = tmp[i][TETROMINO_SIZE - 1 - j];
    }
  }
  reset_position(s);
}

static void reset_position(singleton *s) {
  int min_x = 2;
  int min_y = 2;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.rotated_figure[i][j]) {
        if (i < min_y) {
          min_y = i;
        }
        if (j < min_x) {
          min_x = j;
        }
      }
    }
  }

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.rotated_figure[i][j]) {
        s->figure.rotated_figure[i - min_y][j - min_x] =
            s->figure.rotated_figure[i][j];
        s->figure.rotated_figure[i][j] = 0;
      }
    }
  }
}
