/**
 * @file operations.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../include/tetris/operations.h"

static void reset_position(Model_t *model);
static void get_score(int lines, GameInfo_t *game_info);
static void update_level(GameInfo_t *game_info);

void put_figure(Model_t *model, GameInfo_t *game_info) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (model->figure.current_figure[i][j]) {
        game_info->field[model->figure.y + i][model->figure.x + j] =
            model->figure.current_color;
      }
    }
  }
}

void move_down(Model_t *model, GameInfo_t *game_info) {
  remove_figure(model, game_info);
  model->figure.y++;
  put_figure(model, game_info);
}

void remove_figure(Model_t *model, GameInfo_t *game_info) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (model->figure.current_figure[i][j]) {
        game_info->field[model->figure.y + i][model->figure.x + j] = 0;
      }
    }
  }
}

bool is_out_of_bounds(int new_x, int new_y) {
  return (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT);
}

bool is_collision(Model_t *model, GameInfo_t *game_info, int new_x, int new_y) {
  return game_info->field[new_y][new_x] &&
         !is_inside_figure(model, new_y, new_x);
}

bool can_move(Model_t *model, GameInfo_t *game_info, int dx, int dy) {
  bool result = true;

  for (int i = 0; i < TETROMINO_SIZE && result; i++) {
    for (int j = 0; j < TETROMINO_SIZE && result; j++) {
      if (!model->figure.current_figure[i][j]) {
        continue;
      }

      int new_x = model->figure.x + j + dx;
      int new_y = model->figure.y + i + dy;

      if (is_out_of_bounds(new_x, new_y) ||
          is_collision(model, game_info, new_x, new_y)) {
        result = false;
      }
    }
  }

  return result;
}

bool can_move_left(Model_t *model, GameInfo_t *game_info) {
  return can_move(model, game_info, -1, 0);
}

bool can_move_right(Model_t *model, GameInfo_t *game_info) {
  return can_move(model, game_info, 1, 0);
}

bool can_move_down(Model_t *model, GameInfo_t *game_info) {
  return can_move(model, game_info, 0, 1);
}

void move_left(Model_t *model, GameInfo_t *game_info) {
  if (can_move_left(model, game_info)) {
    remove_figure(model, game_info);
    model->figure.x--;
    put_figure(model, game_info);
  }
}

void move_right(Model_t *model, GameInfo_t *game_info) {
  if (can_move_right(model, game_info)) {
    remove_figure(model, game_info);
    model->figure.x++;
    put_figure(model, game_info);
  }
}

void rotate_figure(Model_t *model, GameInfo_t *game_info) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->figure.current_figure[i][j] = model->figure.rotated_figure[i][j];
      model->figure.rotated_figure[i][j] = 0;
    }
  }
  put_figure(model, game_info);
}

void get_rotated_figure(Model_t *model) {
  int tmp[TETROMINO_SIZE][TETROMINO_SIZE];
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      tmp[i][j] = model->figure.current_figure[j][i];
    }
  }

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->figure.rotated_figure[i][j] = tmp[i][TETROMINO_SIZE - 1 - j];
    }
  }
  reset_position(model);
}
void reset_field(GameInfo_t *game_info) {
  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      game_info->field[i][j] = 0;
    }
  }
}

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

bool can_rotate(Model_t *model, GameInfo_t *game_info) {
  bool res = true;

  remove_figure(model, game_info);
  for (size_t i = 0; i < TETROMINO_SIZE && res; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE && res; j++) {
      if (model->figure.rotated_figure[i][j]) {
        int new_x = model->figure.x + j;
        int new_y = model->figure.y + i;

        if ((new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT ||
             game_info->field[new_y][new_x])) {
          res = false;
          put_figure(model, game_info);
        }
      }
    }
  }

  return res;
}

void check_full_lines(GameInfo_t *game_info) {
  int full_lines = 0;

  for (size_t i = 0; i < HEIGHT; i++) {
    int filled = 1;
    for (size_t j = 0; (j < WIDTH) && (filled != 0); j++) {
      if (!game_info->field[i][j]) {
        filled = 0;
      }
    }
    if (filled) {
      for (size_t k = i; k > 0; k--) {
        for (size_t l = 0; l < WIDTH; l++) {
          game_info->field[k][l] = game_info->field[k - 1][l];
        }
      }
      full_lines++;
      i--;
    }
  }
  get_score(full_lines, game_info);
  update_level(game_info);
}

bool can_put_new_line(Model_t *model, GameInfo_t *game_info) {
  bool res = true;

  for (size_t i = 0; i < TETROMINO_SIZE && res; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE && res; j++) {
      if (game_info->next[i][j] &&
          game_info->field[i + model->figure.y][j + model->figure.x]) {
        res = false;
      }
    }
  }

  return res;
}

static void get_score(int lines, GameInfo_t *game_info) {
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

  game_info->score += score;

  if (game_info->high_score < game_info->score) {
    game_info->high_score = game_info->score;
  }
}

static void update_level(GameInfo_t *game_info) {
  while (game_info->score >= SCORE_PER_LEVEL * (game_info->level)) {
    if (game_info->level < MAX_LEVEL) {
      game_info->level++;
    } else {
      break;
    }
  }
}

static void reset_position(Model_t *model) {
  size_t min_x = 2;
  size_t min_y = 2;

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (model->figure.rotated_figure[i][j]) {
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
      if (model->figure.rotated_figure[i][j]) {
        model->figure.rotated_figure[i - min_y][j - min_x] =
            model->figure.rotated_figure[i][j];
        model->figure.rotated_figure[i][j] = 0;
      }
    }
  }
}
