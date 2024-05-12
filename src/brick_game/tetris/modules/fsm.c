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

void start_stage(singleton *s) {
  reset_game_info(s);
  // generate_new_figure(s); // Пока костыльно вынес в game_loop
  switch (*(s->action)) {
    case Start:
      s->stage = SPAWN;
      break;
    case Terminate:
      s->stage = GAME_OVER;
      break;
  }
}

void game_over_stage(singleton *s) {
  printf("KRASAVA\n");
  ;
}

void spawn_stage(singleton *s) {
  copy_next_to_current(s);
  put_figure(s);
  generate_new_figure(s);
  s->stage = SHIFTING;
}

void shifting_stage(singleton *s) {
  move_down(s);

  switch (*(s->action)) {
    case Left:
    case Right:
    case Down:
      s->stage = MOVING;
      break;
  }
}

void moving_stage(singleton *s) {
  switch (*(s->action)) {
    case Left:
      move_left(s);
      s->stage = SHIFTING;
      break;

    case Right:
      move_right(s);
      s->stage = SHIFTING;
      break;

    case Down:
      move_down(s);
      s->stage = SHIFTING;
      break;
  }
}

void pause_stage(singleton *s) {}

void attaching_stage(singleton *s) {}
