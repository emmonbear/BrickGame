/**
 * @file frontend.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/frontend.h"

/**
 * @brief initializes the terminal in curses mode
 * 
 * @param initscr()   initializes the terminal in curses mode
 * @param cbreak()    disable line bufering
 * @param noecho()    switch off echoing
 * @param keypad()    enables reading of function keys
 * @param timeout(0)  disable timer for waiting for keyboard input
 * @param curs_set(0) make the cursor invisible
 */
void init_screen() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  timeout(0);
  curs_set(0);
}

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

// void game_loop();