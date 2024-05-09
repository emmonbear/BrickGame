/**
 * @file fsm.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/fsm.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void reset_game_info(singleton *s) {
  s->game_info->score = 0;
  s->game_info->high_score = 0;
  s->game_info->level = 1;
  s->game_info->speed = 1;
  s->game_info->pause = 0;
}

static void init_game(singleton *s) {
  setlocale(LC_ALL,
            "");  // Set the locale according to the current system settings.
                  // The locale determines language and regional settings such
                  // as date format, currency, number separators, etc.
  srand(time(NULL));  // initialize the pseudorandom number generator with the
                      // current time
  s->game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));

  if (!s->game_info) {
    MEM_ALLOC_ERROR
  }

  allocate_2d_array(s->game_info->field, HEIGHT, WIDTH);
  allocate_2d_array(s->game_info->next, TETROMINO_SIZE, TETROMINO_SIZE);

  reset_game_info(s);
}

void run_state(singleton *s) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[s->stage](s);
}

void start_stage(singleton *s) { init_game(s); }
