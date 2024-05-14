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

#include <time.h>

static unsigned long long get_current_time() {
  return (unsigned long long)(clock() * 1000 / CLOCKS_PER_SEC);
}

void run_state(singleton *s) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[s->stage](s);
}

void start_stage(singleton *s) {
  // reset_game_info(s);
  // generate_new_figure(s); // Пока костыльно вынес в game_loop
  switch (*(s->action)) {
    case Start:
      s->stage = SPAWN;
      break;
    case Terminate:
      s->stage = GAME_OVER;
      break;
    default:
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
  printf("\r\033[K");
  printf("X = %d\n", s->figure.x);
  unsigned long long current_time = get_current_time();
  if (can_move_down(s)) {
    if (current_time - s->timer >= 1000) {
      move_down(s);
      s->timer = current_time;
    }
  } else {
    s->stage = ATTACHING;
  }
  switch (*(s->action)) {
    case Left:
    case Right:
    case Down:
    case Action:
      moving_stage(s);
      break;
    default:
      break;
  }
}

void moving_stage(singleton *s) {
  s->stage = SHIFTING;

  switch (*(s->action)) {
    case Left:
      move_left(s);
      break;

    case Right:
      move_right(s);
      break;

    case Down:
      if (can_move_down) {
        move_down(s);
      }
      break;
    case Action:
      remove_figure(s);
      rotate_figure(s);
      break;
    default:
      break;
  }
}

void pause_stage(singleton *s) {}

void attaching_stage(singleton *s) {
  s->stage = SPAWN;
  s->figure.x = 3;
  s->figure.y = 0;
}
