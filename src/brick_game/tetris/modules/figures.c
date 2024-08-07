/**
 * @file figure_generator.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/figures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void clear_next(Game_t *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      s->game_info.next[i][j] = 0;
    }
  }
}

/**
 * @brief Copies the next tetromino to the current tetromino.
 *
 * @details
 *
 * This function iterates over the cells of the next tetromino using a nested
 * loop and copies each cell to the corresponding cell of the current tetromino.
 * Then, it copies the color and type of the next tetromino to the current
 * tetromino.
 *
 * @param[in, out] s - A pointer to the Game_t object that contains the
 * game's state and information.
 */
void copy_next_to_current(Game_t *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      s->figure.current_figure[i][j] = s->game_info.next[i][j];
    }
  }
  s->figure.current_color = s->figure.next_color;
  s->figure.current_type = s->figure.next_type;
}

/**
 * @brief Generates a new tetromino and places it in the "next" position.
 *
 * @details
 *
 * This function first clears the "next" position using the clear_next()
 * function. Then, it generates a random number between 0 and NUM_TETROMINOS - 7
 * (inclusive) using the rand() function. If the generated number is equal to
 * the current tetromino's type, it generates a new number until it is
 * different. The function then sets the "next" tetromino's color and type based
 * on the generated number, and sets its position on the game field using the x
 * and y coordinates of the "next" position.
 *
 * @param[in, out] s - A pointer to the Game_t object that contains the
 * game's state and information.
 */
void generate_new_figure(Game_t *s) {
  clear_next(s);

  size_t tmp;
  do {
    tmp = rand() % NUM_TETROMINOS;
  } while (tmp == s->figure.current_type);

  s->figure.next_color = tmp + 1;
  s->figure.next_type = tmp;
  s->figure.x = 3;
  s->figure.y = 0;

  switch (s->figure.next_type) {
    case TET_I:
      s->game_info.next[0][0] = s->game_info.next[0][1] =
          s->game_info.next[0][2] = s->game_info.next[0][3] =
              s->figure.next_color;
      break;

    case TET_Z:
      s->game_info.next[0][0] = s->game_info.next[0][1] =
          s->game_info.next[1][1] = s->game_info.next[1][2] =
              s->figure.next_color;
      break;

    case TET_S:
      s->game_info.next[1][0] = s->game_info.next[1][1] =
          s->game_info.next[0][1] = s->game_info.next[0][2] =
              s->figure.next_color;
      break;

    case TET_T:
      s->game_info.next[0][0] = s->game_info.next[0][1] =
          s->game_info.next[0][2] = s->game_info.next[1][1] =
              s->figure.next_color;
      break;

    case TET_L:
      s->game_info.next[0][0] = s->game_info.next[0][1] =
          s->game_info.next[0][2] = s->game_info.next[1][0] =
              s->figure.next_color;
      break;

    case TET_J:
      s->game_info.next[0][0] = s->game_info.next[1][0] =
          s->game_info.next[1][1] = s->game_info.next[1][2] =
              s->figure.next_color;
      break;

    case TET_O:
      s->game_info.next[0][0] = s->game_info.next[0][1] =
          s->game_info.next[1][0] = s->game_info.next[1][1] =
              s->figure.next_color;
      break;
  }
}
