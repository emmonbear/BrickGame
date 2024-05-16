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

static void get_score(int lines, singleton *s);
static void update_level(singleton *s);

bool is_inside_figure(singleton *s, int y, int x) {
  bool res = false;
  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = 0; j < TETROMINO_SIZE; j++) {
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

  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = TETROMINO_SIZE - 1; j > 0; j--) {
      if (s->figure.current_figure[i][j]) {
        if (s->figure.x + j > WIDTH - 2) {
          res = false;
          break;
        } else if (s->game_info->field[s->figure.y + i][s->figure.x + j + 1] &&
                   !is_inside_figure(s, s->figure.y + i, s->figure.x + j + 1)) {
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

bool can_rotate(singleton *s) {
  bool res = true;

  remove_figure(s);
  for (size_t i = 0; i < TETROMINO_SIZE && res; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE && res; j++) {
      if (s->figure.rotated_figure[i][j]) {
        int new_x = s->figure.x + j;
        int new_y = s->figure.y + i;

        if ((new_x < 0 || new_x >= WIDTH ||
             s->game_info->field[new_y][new_x])) {
          res = false;
          put_figure(s);
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

void check_full_lines(singleton *s) {
  int full_lines = 0;

  for (size_t i = 0; i < HEIGHT; i++) {
    int filled = 1;
    for (size_t j = 0; (j < WIDTH) && (filled != 0); j++) {
      if (!s->game_info->field[i][j]) {
        filled = 0;
      }
    }
    if (filled) {
      for (size_t k = i; k > 0; k--) {
        for (size_t l = 0; l < WIDTH; l++) {
          s->game_info->field[k][l] = s->game_info->field[k - 1][l];
        }
      }
      full_lines++;
      i--;
    }
  }
  get_score(full_lines, s);
  update_level(s);
}

static void get_score(int lines, singleton *s) {
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

  s->game_info->score += score;

  if (s->game_info->high_score < s->game_info->score) {
    s->game_info->high_score = s->game_info->score;
  }
}

static void update_level(singleton *s) {
  while (s->game_info->score >= SCORE_PER_LEVEL * (s->game_info->level)) {
    if (s->game_info->level < MAX_LEVEL) {
      s->game_info->level++;
    } else {
      break;
    }
  }
}

bool can_put_new_line(singleton *s) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE && res; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE && res; j++) {
      if (s->game_info->next[i][j] &&
          s->game_info->field[i + s->figure.y][j + s->figure.x]) {
        res = false;
      }
    }
  }

  return res;
}