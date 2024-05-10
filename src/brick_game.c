/**
 * @file brick_game.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// #include "./gui/cli/include/frontend.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./brick_game/tetris/include/fsm.h"

static singleton *get_instance() {
  static singleton instance;
  return &instance;
}

int main() {
  singleton *s = get_instance();
  start_stage(s);

  while(s->stage != GAME_OVER) {
    run_state(s);
  }
  game_over_stage(s);
  return 0;
}
