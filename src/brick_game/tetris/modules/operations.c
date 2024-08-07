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
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void put_figure(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.current_figure[i][j]) {
        s->game_info.field[s->figure.y + i][s->figure.x + j] =
            s->figure.current_color;
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
 * @param[in, out] s A pointer to the singleton object that contains the
 game's state and information.

 */
void move_down(singleton *s) {
  remove_figure(s);
  s->figure.y++;
  put_figure(s);
}

/**
 * @brief Removes the current figure from the game field.
 *
 * This function iterates over the cells of the current figure and, if a cell is
 * occupied, sets the corresponding cell in the game field to 0 (empty).
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void remove_figure(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->figure.current_figure[i][j]) {
        s->game_info.field[s->figure.y + i][s->figure.x + j] = 0;
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
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void move_left(singleton *s) {
  if (can_move_left(s)) {
    remove_figure(s);
    s->figure.x--;
    put_figure(s);
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
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void move_right(singleton *s) {
  if (can_move_right(s)) {
    remove_figure(s);
    s->figure.x++;
    put_figure(s);
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
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void rotate_figure(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      s->figure.current_figure[i][j] = s->figure.rotated_figure[i][j];
      s->figure.rotated_figure[i][j] = 0;
    }
  }
  put_figure(s);
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
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
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
  size_t min_x = 2;
  size_t min_y = 2;

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

/**
 * @brief Resets the game field to its initial state.
 *
 * @details
 * This function iterates over the cells of the game field using a nested loop
 * and sets each cell to 0 (empty).
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information
 */
void reset_field(singleton *s) {
  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      s->game_info.field[i][j] = 0;
    }
  }
}