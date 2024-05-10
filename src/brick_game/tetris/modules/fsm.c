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

// #include <locale.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

void run_state(singleton *s) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[s->stage](s);
}

void start_stage(singleton *s) { init_game(s); }

void game_over_stage(singleton *s) { destroy_game(s); }

void spawn_stage(singleton *s) {
  s->figure = generate_new_figure();
  s->game_info->next = s->figure.cells;
}

void shifting_stage(singleton *s) {}

void moving_stage(singleton *s) {}

void pause_stage(singleton *s) {}

void attaching_stage(singleton *s) {}
