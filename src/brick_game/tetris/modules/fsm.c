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

static int get_current_time() { return (int)(clock() * 1000 / CLOCKS_PER_SEC); }

void run_state(singleton *s) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[s->stage](s);
}

void start_stage(singleton *s) {
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
  write_high_score(s);

  switch (*(s->action)) {
    case Start:
      s->stage = SPAWN;
      break;
    case Terminate:
      s->game_over = 1;
      break;
    default:
      break;
  }
}

void spawn_stage(singleton *s) {
  copy_next_to_current(s);
  put_figure(s);
  generate_new_figure(s);
  s->stage = SHIFTING;
}

void shifting_stage(singleton *s) {
  int current_time = get_current_time();
  int wait_time = 1000 - (s->game_info->level * 100);

  if (wait_time < 100) {
    wait_time = 100;
  }

  if (can_move_down(s)) {
    if (current_time - s->timer >= wait_time) {
      move_down(s);
      s->timer = current_time;
    }
  } else {
    if ((current_time - s->timer >= wait_time)) {
      s->stage = ATTACHING;
    }
  }
  switch (*(s->action)) {
    case Left:
    case Right:
    case Down:
    case Action:
      moving_stage(s);
      break;
    case Terminate:
      s->stage = GAME_OVER;
      break;
    case Pause:
      s->stage = PAUSE;
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
      if (can_move_down(s)) {
        move_down(s);
      }
      break;
    case Action:
      get_rotated_figure(s);

      if (can_rotate(s)) {
        rotate_figure(s);
      }

      break;
    default:
      break;
  }
}

void pause_stage(singleton *s) {
  switch (*(s->action)) {
    case Pause:
      s->stage = SHIFTING;
      break;
    case Terminate:
      s->stage = GAME_OVER;
      break;
    default:
      break;
  }
}

void attaching_stage(singleton *s) {
  check_full_lines(s);
  s->figure.x = 3;
  s->figure.y = 0;

  if (can_put_new_line(s)) {
    s->stage = SPAWN;
  } else {
    s->stage = GAME_OVER;
  }
}
