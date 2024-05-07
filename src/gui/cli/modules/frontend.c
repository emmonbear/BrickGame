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
#include <string.h>

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
  WINDOW *board, *next;
  printw ("HEIGHT = %d\n", HEIGHT);
  printw ("WIDTH = %d\n", WIDTH);
  printw ("FULL_HEIGHT = %d\n", FIELD_HEIGHT);
  printw ("FULL_WIDTH = %d\n", FIELD_WIDTH);
  printw ("Y_CENTER = %d\n", Y_CENTER_FIELD);
  printw ("X_CENTER = %d\n", X_CENTER_FIELD);
  printw ("NEXT_HEIGHT = %d\n", NEXT_HEIGHT);
  printw ("LINES = %d\n", LINES);
  printw ("COLS = %d\n", COLS);
  // UserAction_t action;
  bool game = TRUE;



  refresh();

  board = newwin(FIELD_HEIGHT, FIELD_WIDTH, Y_CENTER_FIELD, X_CENTER_FIELD);
  next = newwin(NEXT_HEIGHT, NEXT_WIDTH, Y_CENTER_NEXT, X_CENTER_NEXT);
  printw ("NEXT_HEIGHT = %d\n", NEXT_HEIGHT);


  while (game) {
    // int cnt = 0;
    generate_new_figure();
    print_field(board);
    printf_next(next);
    // get_user_input(&action);
    getch();
    // if (cnt == 5) {
      game = false;
    // }
    // cnt++;
  }
}

void print_field(WINDOW *w) {
  singleton *s = get_instance();
  box(w, 0, 0);
  for (int i = 0; i < HEIGHT; i++) {
    wmove(w, i + 1, 1);
    for (int j = 0; j < WIDTH; j++) {
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
  
  int center_x = (NEXT_WIDTH - strlen("NEXT")) / 2;
  mvwaddch(w, 2, 1, ACS_ULCORNER);
  mvwaddch(w, 2, 10, ACS_URCORNER);
  mvwaddch(w, 7, 1, ACS_LLCORNER);
  mvwaddch(w, 7, 10, ACS_LRCORNER);

  mvwhline(w, 2, 2, ACS_HLINE, 8);
  mvwhline(w, 7, 2, ACS_HLINE, 8);

  mvwvline(w, 3, 1, ACS_VLINE, 4);
  mvwvline(w, 3, 10, ACS_VLINE, 4);

  mvwprintw(w, 1, center_x, "NEXT");
  for (int i = 0; i < TETROMINO_SIZE; i++) {
    wmove(w, i + 3, 2);
    for (int j = 0; j < TETROMINO_SIZE; j++) {
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