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
  // reset_game_info(s);
  // generate_new_figure(s);
  printf("!!!!!%d\n", *(s->action));
  
  switch(*(s->action)) {
    case Start:
      printf("Start\n");

      *(s->action) = START;
      break;
    case Terminate:
      printf("Terminate\n");

      *(s->action) = GAME_OVER;
      break;
    default:
      *(s->action) = GAME_OVER;
      printf("default\n");
      break;
  }
}

void game_over_stage(singleton *s) { 
  destroy_game(s);
  }

void spawn_stage(singleton *s) {
  copy_next_to_current(s);
  put_figure(s);
  generate_new_figure(s);

  switch(*(s->action)) {
    Terminate:
      printf("1\n");
      s->stage = GAME_OVER;
      break;
    Start:
      printf("2\n");

      s->stage = START;
      break;
  }
}

void shifting_stage(singleton *s) {
  printf("SHIFTING_STAGE\n");
  move_down(s);
}

void moving_stage(singleton *s) { move_right(s); }

void pause_stage(singleton *s) {}

void attaching_stage(singleton *s) {}
