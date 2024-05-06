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

#include "./gui/cli/include/frontend.h"
#include <stdio.h>

int main() {
  init_game();
  init_screen();
  
  game_loop();

  wclear(stdscr);
  endwin();
  destroy_game();
  
  return 0;
}