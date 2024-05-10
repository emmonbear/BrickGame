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

void run_state(singleton *s) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[s->stage](s);
}

static void test_field(singleton *s) {
  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      printf("%d ", s->game_info->field[i][j]);
    }
    putchar('\n');
  }
}

void start_stage(singleton *s) {
  init_game(s);
  generate_new_figure(s);
}

void game_over_stage(singleton *s) { destroy_game(s); }

void spawn_stage(singleton *s) {
  put_figure_on_field(s);
  test_field(s);
  putchar('\n');

  generate_new_figure(s);
  put_figure_on_field(s);
  test_field(s);
  // test(s);
  s->stage = GAME_OVER;
}

void shifting_stage(singleton *s) {}

void moving_stage(singleton *s) {}

void pause_stage(singleton *s) {}

void attaching_stage(singleton *s) {}
