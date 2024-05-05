/**
 * @file brick_game.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Main function
 * @version 1.0
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./brick_game.h"
#include <stdio.h>

#include <ncurses.h>

/**
 * @brief Get the user input object
 * 
 * @param[out] action
 * @todo Необходимо будет исправить case default
 */
void get_user_input(UserAction_t *action) {
  switch(getch()) {
    case KEY_LEFT:
      *action = Left;
      break;
    case KEY_RIGHT:
      *action = Right;
      break;
    case KEY_DOWN:
      *action = Down;
      break;
    case ' ':
      *action = Action;
      break;
    case '\n':
      *action = Start;
      break;
    case 'p':
    case 'P':
      *action = Pause;
      break;
    case 'q':
    case 'Q':
      *action = Terminate;
      break;
    default:
      printw("NONE");
      break;
  }
}

int main() {
  UserAction_t action;
  WINDOW *field;

  INIT_SCR

  endwin();
}
