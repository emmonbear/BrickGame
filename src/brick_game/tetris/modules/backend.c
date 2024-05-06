/**
 * @file backend.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/backend.h"

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

/**
 * @brief Get the instance object
 * 
 * @return singleton* 
 */
singleton *get_instance() {
  static singleton instance;
  return &instance;
}

void init_game() {
  setlocale(LC_ALL, "");
  singleton *s = get_instance();
  s->game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));

  if (!s->game_info) {
    MEM_ALLOC_ERROR
  }
  s->game_info->field = (int **)calloc(F_ROWS, sizeof(int *));
  s->game_info->next = (int **)calloc(T_SIZE, sizeof(int *));

  if ((!s->game_info->field) || (!s->game_info->next)) {
    destroy_game(s);
    MEM_ALLOC_ERROR
  }

  for (int i = 0; i < F_ROWS; i++) {
    s->game_info->field[i] = (int *)calloc((F_COLS * C_SIZE), sizeof(int));
    if(!s->game_info->field[i]) {
      destroy_game(s);
      MEM_ALLOC_ERROR
    }
  }

  for (int i = 0; i < T_SIZE; i++) {
    s->game_info->next[i] = (int *)calloc((T_SIZE * C_SIZE), sizeof(int));
    if (!s->game_info->next[i]) {
      destroy_game(s);
      MEM_ALLOC_ERROR
    }
  }

  s->game_info->score = 0;
  s->game_info->high_score = 0;
  s->game_info->level = 1;
  s->game_info->speed = 1;
  s->game_info->pause = 0;
}

/**
 * @brief Clear allocated memory
 * 
 * @param[out] s 
 */
void destroy_game () {
  singleton *s = get_instance();
  
  if (s->game_info) {
    if (s->game_info->field) {
      for (int i = 0; i < F_ROWS; i++) {
        if (s->game_info->field[i]) {
          free(s->game_info->field[i]);
          s->game_info->field[i] = NULL;
        }
      }
      free(s->game_info->field);
      s->game_info->field = NULL;
    }

    if (s->game_info->next) {
      for (int i = 0; i < T_SIZE; i++) {
        if (s->game_info->next[i]) {
          free(s->game_info->next[i]);
          s->game_info->next[i] = NULL;
        }
      }
      free(s->game_info->next);
      s->game_info->next = NULL;
    }
    free(s->game_info);
    s->game_info = NULL;
  }
}
