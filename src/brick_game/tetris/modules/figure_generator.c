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

#include "../include/figure_generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_new_figure(singleton *s) {
  clear_next(s);
  int tmp = rand() % NUM_TETROMINOS;
  s->figure.color = tmp + 1;
  s->figure.type = tmp;
  s->figure.rotation = 0;
  s->figure.x = 3;
  s->figure.y = 0;

  switch (s->figure.type) {
    case TET_I:
      s->game_info->next[0][0] = s->game_info->next[0][1] =
          s->game_info->next[0][2] = s->game_info->next[0][3] = 1;
      break;

    case TET_Z:
      s->game_info->next[0][0] = s->game_info->next[0][1] =
          s->game_info->next[1][1] = s->game_info->next[1][2] = 1;
      break;

    case TET_S:
      s->game_info->next[0][1] = s->game_info->next[0][2] =
          s->game_info->next[1][0] = s->game_info->next[1][1] = 1;
      break;

    case TET_T:
      s->game_info->next[0][1] = s->game_info->next[1][0] =
          s->game_info->next[1][1] = s->game_info->next[1][2] = 1;
      break;

    case TET_L:
      s->game_info->next[0][0] = s->game_info->next[0][1] =
          s->game_info->next[0][2] = s->game_info->next[1][2] = 1;
      break;

    case TET_J:
      s->game_info->next[0][0] = s->game_info->next[0][1] =
          s->game_info->next[0][2] = s->game_info->next[1][0] = 1;
      break;

    case TET_O:
      s->game_info->next[0][0] = s->game_info->next[0][1] =
          s->game_info->next[1][0] = s->game_info->next[1][1] = 1;
      break;
  }
}

void clear_next(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      s->game_info->next[i][j] = 0;
    }
  }
}
void put_figure_on_field(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->game_info->next[i][j]) {
        s->game_info->field[s->figure.y + i][s->figure.x + j] = s->figure.color;
      }
    }
  }
}
