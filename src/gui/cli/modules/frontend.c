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
  // cbreak();
  // noecho();
  keypad(stdscr, TRUE);
  // timeout(0);
  curs_set(0);
}

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
      printw("NONE");
      break;
  }
}

void game_loop() {
  singleton *s = get_instance();
  WINDOW *board;
  WINDOW *next;
  // UserAction_t action;
  bool game = TRUE;
  int height = F_ROWS + BOARD_SIZE;
  int width = (C_SIZE * F_COLS) + BOARD_SIZE;
  int start_y = (LINES - height) / 2;
  int start_x = (COLS - width) / 2;
  // int CCENTER =

  refresh();
  printw("height = %d\n", height);
  printw("width = %d\n", width);
  printw("start_y = %d\n", start_y);
  printw("start_x = %d\n", start_x);
  printw("LINES = %d\n", LINES);
  printw("COLS = %d\n", COLS);
  board = newwin(height, width, start_y, start_x);
  next = newwin((T_SIZE * 2) + BOARD_SIZE, (T_SIZE * 4) + BOARD_SIZE, start_y,
                start_x + start_x / 3);

  while (game) {
    generate_new_figure();
    print_field(board);
    printf_next(next);
    // get_user_input(&action);
    // wrefresh(next);
    getch();
    game = false;
  }
}

void print_field(WINDOW *w) {
  singleton *s = get_instance();
  box(w, 0, 0);
  for (int i = 0; i < F_ROWS; i++) {
    wmove(w, i + 1, 1);
    for (int j = 0; j < F_COLS; j++) {
      if (s->game_info->field[i][j] == 1) {
        waddch(w, ' ');
        waddch(w, ' ');
      } else {
        waddch(w, '[');
        waddch(w, ']');
      }
    }
  }
  wrefresh(w);
}

void printf_next(WINDOW *w) {
  singleton *s = get_instance();
  box(w, 0, 0);
  for (int i = 0; i < T_SIZE; i++) {
    wmove(w, i + 1, 2);
    for (int j = 0; j < T_SIZE; j++) {
      if (s->game_info->next[i][j] == 1) {
        waddch(w, '[');
        waddch(w, ']');
      } else {
        waddch(w, ' ');
        waddch(w, ' ');
      }
    }
  }
  wrefresh(w);
}