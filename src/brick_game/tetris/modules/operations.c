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

static void reset_position(Model_t *model);

/**
 * @brief Places the current tetromino figure onto the game field.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino figure and
 * updates the corresponding cells in the game field with the color of the
 * current tetromino. The position on the game field is determined by the
 * current coordinates of the tetromino figure.
 *
 * @param model A pointer to the game model containing the current tetromino
 * figure and the game field.
 */
void put_figure(Model_t *model) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (model->figure.current_figure[i][j]) {
        model->game_info.field[model->figure.y + i][model->figure.x + j] =
            model->figure.current_color;
      }
    }
  }
}

/**
 * @brief Moves the current tetromino figure down by one row.
 *
 * @details
 *
 * This function removes the current tetromino figure from its current position
 * on the game field, updates its vertical position to move it one row down, and
 * then places the tetromino figure back onto the game field at the new
 * position.
 *
 * @param model A pointer to the game model containing the current tetromino
 * figure and the game field.
 */
void move_down(Model_t *model) {
  remove_figure(model);
  model->figure.y++;
  put_figure(model);
}

/**
 * @brief Removes the current tetromino figure from the game field.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino figure and
 * clears the corresponding cells in the game field by setting them to 0. This
 * effectively removes the tetromino from the game field, allowing for a new
 * position to be calculated or a new tetromino to be placed.
 *
 * @param model A pointer to the game model containing the current tetromino
 * figure and the game field.
 */
void remove_figure(Model_t *model) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (model->figure.current_figure[i][j]) {
        model->game_info.field[model->figure.y + i][model->figure.x + j] = 0;
      }
    }
  }
}

/**
 * @brief Moves the current tetromino figure left by one column.
 *
 * @details
 *
 * This function first checks if the current tetromino figure can move left by
 * verifying that there is no collision with the game field boundaries or other
 * figures. If the move is possible, the function removes the tetromino from its
 * current position, updates its horizontal position to move it one column left,
 * and then places the tetromino back onto the game field at the new position.
 *
 * @param model A pointer to the game model containing the current tetromino
 * figure and the game field.
 */
void move_left(Model_t *model) {
  if (can_move_left(model)) {
    remove_figure(model);
    model->figure.x--;
    put_figure(model);
  }
}

/**
 * @brief Moves the current tetromino figure right by one column.
 *
 * @details
 *
 * This function first checks if the current tetromino figure can move right by
 * verifying that there is no collision with the game field boundaries or other
 * figures. If the move is possible, the function removes the tetromino from its
 * current position, updates its horizontal position to move it one column
 * right, and then places the tetromino back onto the game field at the new
 * position.
 *
 * @param model A pointer to the game model containing the current tetromino
 * figure and the game field.
 */
void move_right(Model_t *model) {
  if (can_move_right(model)) {
    remove_figure(model);
    model->figure.x++;
    put_figure(model);
  }
}

/**
 * @brief Rotates the current tetromino figure and places it on the game field.
 *
 * @details
 *
 * This function updates the `current_figure` of the model to match the
 * `rotated_figure` which represents the new orientation of the tetromino. It
 * first copies the contents of `rotated_figure` into `current_figure` and
 * clears the `rotated_figure`. After updating the figure's orientation, the
 * function places the updated figure onto the game field at its current
 * position.
 *
 * @param model A pointer to the game model containing the tetromino figure and
 * the game field.
 */
void rotate_figure(Model_t *model) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->figure.current_figure[i][j] = model->figure.rotated_figure[i][j];
      model->figure.rotated_figure[i][j] = 0;
    }
  }
  put_figure(model);
}

/**
 * @brief Computes the rotated version of the current tetromino figure.
 *
 * @details
 *
 * This function calculates the rotated version of the `current_figure` and
 * stores it in `rotated_figure`. It first transposes the `current_figure`
 * matrix and then reverses the columns to achieve a 90-degree clockwise
 * rotation. After calculating the rotated figure, it resets the position of the
 * tetromino.
 *
 * @param model A pointer to the game model containing the tetromino figure.
 */
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

/**
 * @brief Resets the game field to its initial state.
 *
 * @details
 *
 * This function sets all cells in the game field to zero, effectively clearing
 * the entire game board. It iterates through every cell in the field and
 * assigns a value of zero to indicate that no tetrominoes are present on the
 * board.
 *
 * @param model A pointer to the game model containing the game field.
 */
void reset_field(Model_t *model) {
  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      model->game_info.field[i][j] = 0;
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
