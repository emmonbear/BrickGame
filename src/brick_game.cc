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
#include "./gui/cli/include/view.h"
}

int main() {
  init_screen();
  View_t *view = init_view();

  if (!view) {
    endwin();
    MEM_ALLOC_ERROR;
    return 1;
  }

  game_loop(view);
  destroy_view(view);
  endwin();

  return 0;
}
