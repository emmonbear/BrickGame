/**
 * @file input_gui.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/input_gui.h"

void get_user_input(UserAction_t *action) {
  switch (getch()) {
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
      *action = -1;
      break;
  }
}