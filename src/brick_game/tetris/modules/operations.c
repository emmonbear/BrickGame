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
 * @brief Puts the current tetromino on the game field.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino and, if a cell
 * is occupied, sets the corresponding cell of the game field to the color of
 * the current tetromino. The function does not check if the current tetromino
 * collides with other tetrominoes or the boundaries of the game field.
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 * game's state and information.
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
 * @brief Moves the current figure down by one unit.
 *
 * @details
 *
 * This function removes the current figure from the game field, increments the
 * vertical coordinate of the figure by one, and then puts the figure back on
 * the game field.
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 game's state and information.

 */
void move_down(Model_t *model) {
  remove_figure(model);
  model->figure.y++;
  put_figure(model);
}

/**
 * @brief Removes the current figure from the game field.
 *
 * This function iterates over the cells of the current figure and, if a cell is
 * occupied, sets the corresponding cell in the game field to 0 (empty).
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 * game's state and information.
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
 * @brief Moves the current figure one unit to the left.
 *
 * @details
 *
 * This function first checks if the figure can be moved to the left using the
 * can_move_left() function. If the function returns true, the function removes
 * the figure from the game field using the remove_figure() function, decrements
 * the x-coordinate of the figure by one, and then puts the figure back on the
 * game field using the put_figure() function.
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 * game's state and information.
 */
void move_left(Model_t *model) {
  if (can_move_left(model)) {
    remove_figure(model);
    model->figure.x--;
    put_figure(model);
  }
}

/**
 * @brief Moves the current figure one unit to the right.
 *
 * @details
 *
 * This function first checks if the figure can be moved to the right using the
 * can_move_right() function. If the function returns true, the function removes
 * the figure from the game field using the remove_figure() function, increments
 * the x-coordinate of the figure by one, and then puts the figure back on the
 * game field using the put_figure() function.
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 * game's state and information.
 */
void move_right(Model_t *model) {
  if (can_move_right(model)) {
    remove_figure(model);
    model->figure.x++;
    put_figure(model);
  }
}

/**
 * @brief Rotates the current figure on the game field.
 *
 * @details
 *
 * This function first copies the current figure's rotation state into the
 * current figure's matrix using a nested loop. Then, it removes the current
 * figure from the game field using the remove_figure() function, and puts the
 * rotated figure back on the game field using the put_figure() function.
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 * game's state and information.
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
 * @brief Generates a rotated version of the current figure.
 *
 * @details
 *
 * This function first transposes the current figure's matrix using a nested
 * loop and a temporary matrix. Then, it reverses the columns of the transposed
 * matrix using another nested loop and stores the result in the current
 * figure's rotated matrix. Finally, it shifts the resulting shape relative to
 * the top left block
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 * game's state and information.
 */
void get_rotated_figure(Model_t *model) {
  // Transpose matrix
  int tmp[TETROMINO_SIZE][TETROMINO_SIZE];
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      tmp[i][j] = model->figure.current_figure[j][i];
    }
  }

  // Reversing columns
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      model->figure.rotated_figure[i][j] = tmp[i][TETROMINO_SIZE - 1 - j];
    }
  }
  reset_position(model);
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

/**
 * @brief Resets the game field to its initial state.
 *
 * @details
 * This function iterates over the cells of the game field using a nested loop
 * and sets each cell to 0 (empty).
 *
 * @param[in, out] s A pointer to the Model_t object that contains the
 * game's state and information
 */
void reset_field(Model_t *model) {
  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      model->game_info.field[i][j] = 0;
    }
  }
}
