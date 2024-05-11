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

void put_figure(singleton *s) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (s->game_info->next[i][j]) {
        s->game_info->field[s->figure.y + i][s->figure.x + j] = s->figure.current_color;
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
      if (s->game_info->next[i][j]) {
        s->game_info->field[s->figure.y + i][s->figure.x + j] = 0;
      }
    }
  }
}
