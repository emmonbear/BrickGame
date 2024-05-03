/**
 * @file init.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/init.h"
#include "../include/defines.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * @brief 
 * 
 * @return GameInfo_t 
 */
GameInfo_t *init_game(void) {
  GameInfo_t *game_info = (GameInfo_t *)calloc(1, sizeof(GameInfo_t));
  if (!game_info) {
    fprintf(stderr, "Memory allocation error\n");
    return NULL;
  }
  game_info->field = (int **)calloc(ROWS, sizeof(int *));
  game_info->next = (int **)calloc(ROWS, sizeof(int *));

  if (!game_info->field || !game_info->next) {
    fprintf(stderr, "Memory allocation error\n");
    destrust_game(game_info);
    return NULL;
  }

  for (int i = 0; i < ROWS; i++) {
    game_info->field[i] = (int *)calloc(COLS, sizeof(int));
    game_info->next[i] = (int *)calloc(COLS, sizeof(int));
    if(!game_info->field[i] || !game_info->next[i]) {
      fprintf(stderr, "Memory allocation error\n");
      destrust_game(game_info);
      return NULL;
    }
  }

  game_info->level = 1;
  game_info->high_score = 0;
  game_info->pause = 0;
  game_info->speed = 1;

  return game_info;
}

/**
 * @brief 
 * 
 * @param[out] game_info 
 */
void destrust_game(GameInfo_t *game_info) {
  if (game_info) {
    if(game_info->field) {
      for (int i = 0; i < ROWS; i++) {
        if (game_info->field[i]) {
          free(game_info->field[i]);
          game_info->field[i] = NULL;
        }
      }
      free(game_info->field);
      game_info->field = NULL;
    }
    if(game_info->next) {
      for (int i = 0; i < ROWS; i++) {
        if (game_info->next[i]) {
          free(game_info->next[i]);
          game_info->next[i] = NULL;
        }
      }
      free(game_info->next);
      game_info->next = NULL;
    }
    free(game_info);
  }
}