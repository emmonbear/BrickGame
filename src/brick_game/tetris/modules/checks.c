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

/**
 * @brief Checks if a specific coordinate on the game board is within the bounds
 of the current tetromino figure.
 *
 * @details
 *
 * This function iterates through the shape of the current tetromino figure and
 * checks if the given
 * coordinates (`y`, `x`) match any part of the figure's shape on the gameboard.
 * It compares the provided
 * coordinates with each occupied cell of the tetromino figure's shape,
 * accounting for the figure's current
 * position on the board.
 *
 * @param model A pointer to the game model containing the current figure.
 * @param y The y-coordinate on the game board.
 * @param x The x-coordinate on the game board.
 * @return true if the coordinates are within the figure, false otherwise.
 */
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

/**
 * @brief Checks if the current tetromino figure can move right on the game
 * board.
 *
 * @details
 *
 * This function determines if the tetromino figure can be moved one step to the
 * right without colliding with the game board boundaries or other placed
 * blocks. It checks each block of the current figure to ensure that moving it
 * to the right does not exceed the board width or overlap with existing blocks,
 * considering both the boundaries and occupied cells on the board.
 *
 * @param model A pointer to the game model containing the current figure and
 * game field.
 * @return true if the tetromino can move right, false otherwise.
 */
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

/**
 * @brief Checks if the current tetromino figure can move left on the game
 * board.
 *
 * @details
 *
 * This function determines if the tetromino figure can be moved one step to the
 * left without colliding with the game board boundaries or other placed blocks.
 * It checks each block of the current figure to ensure that moving it to the
 * left does not go beyond the left edge of the board or overlap with existing
 * blocks, considering both the boundaries and occupied cells on the board.
 *
 * @param model A pointer to the game model containing the current figure and
 * game field.
 * @return true if the tetromino can move left, false otherwise.
 */
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

/**
 * @brief Checks if the current tetromino figure can be rotated on the game
 * board.
 *
 * @details
 *
 * This function determines if the tetromino figure can be rotated without
 * colliding with the game board boundaries or other placed blocks. It
 * temporarily removes the figure, checks each block of the rotated figure to
 * ensure that rotating it does not exceed the board boundaries or overlap with
 * existing blocks, and then restores the figure to its original state.
 *
 * @param model A pointer to the game model containing the current figure and
 * game field.
 * @return true if the tetromino can be rotated, false otherwise.
 */
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

/**
 * @brief Checks if the current tetromino figure can move down on the game
 * board.
 *
 * @details
 *
 * This function determines if the tetromino figure can be moved one step down
 * without colliding with the game board boundaries or other placed blocks. It
 * checks each block of the current figure to ensure that moving it downward
 * does not exceed the board height or overlap with existing blocks, considering
 * both the boundaries and occupied cells on the board.
 *
 * @param model A pointer to the game model containing the current figure and
 * game field.
 * @return true if the tetromino can move down, false otherwise.
 */
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

/**
 * @brief Checks and clears full lines in the game field, and updates the score
 * and level.
 *
 * @details
 *
 * This function iterates through each row of the game field to identify full
 * lines (rows where all cells are filled). For each full line found, it shifts
 * all rows above it down by one row to clear the full line. After processing
 * all rows, it updates the game score and level based on the number of full
 * lines cleared.
 *
 * @param model A pointer to the game model containing the game field and other
 * relevant information.
 */
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

/**
 * @brief Checks if a new tetromino figure can be placed on the game board
 * without collision.
 *
 * @details
 *
 * This function determines if the next tetromino figure can be placed on the
 * game board without overlapping with existing blocks. It checks each block of
 * the next figure against the current state of the game field to ensure that
 * placing the new figure does not collide with already placed blocks.
 *
 * @param model A pointer to the game model containing the game field and the
 * next figure information.
 * @return true if the new figure can be placed, false otherwise.
 */
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
