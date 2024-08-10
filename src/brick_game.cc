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

extern "C" {
#include "./brick_game/tetris/include/model.h"
#include "./controller/tetris/include/controller.h"
#include "./gui/cli/include/view.h"
}

int main() {
  init_screen();
  Controller_t *controller = init_controller();

  if (!controller) {
    endwin();
    MEM_ALLOC_ERROR;
    return 1;
  }

  game_loop(controller);
  destroy_controller(controller);
  endwin();

  return 0;
}
