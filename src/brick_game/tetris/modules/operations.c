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

void rotate_figure(singleton *s) {
  int tmp[TETROMINO_SIZE][TETROMINO_SIZE];

  // Transpose matrix
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      tmp[i][j] = s->figure.current_figure[j][i];
    }
  }

  // Reversing columns
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      s->figure.current_figure[i][j] = tmp[i][TETROMINO_SIZE - 1 - j];
    }
  }
  reset_position(s);
}

static void reset_position(singleton *s) {
  int min_x = TETROMINO_SIZE / 2;
  int min_y = TETROMINO_SIZE / 2;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.current_figure[i][j]) {
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
      if (s->figure.current_figure[i][j]) {
        s->figure.current_figure[i - min_y][j - min_x] =
            s->figure.current_figure[i][j];
        s->figure.current_figure[i][j] = 0;
      }
    }
  }
}
