/**
 * @file view.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../include/gui/cli/view.h"

static void init_window(window_t *window, int height, int width, int y, int x);
static void destroy_window(window_t *window);

void init_screen() {
  initscr();              // Initialize ncurses mode
  raw();                  // Disable line buffering
  nodelay(stdscr, TRUE);  // Set non-blocking input
  noecho();               // Disable echoing of typed characters
  keypad(stdscr, TRUE);   // Enable special keys to be read
  curs_set(0);            // Hide the cursor
  start_color();          // Enable color functionality

  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void init_windows(Windows_t *windows) {
  if (!windows) {
    MEM_ALLOC_ERROR;
  }
  init_window(&windows->field, FIELD_HEIGHT, FIELD_WIDTH, Y_CENTER_FIELD,
              X_CENTER_FIELD);
  init_window(&windows->next, NEXT_HEIGHT, NEXT_WIDTH, Y_CENTER_NEXT,
              X_CENTER_NEXT);
  init_window(&windows->score, SCORE_HEIGHT, SCORE_WIDTH, Y_CENTER_SCORE,
              X_CENTER_SCORE);
  init_window(&windows->high_score, HIGH_SCORE_HEIGHT, HIGH_SCORE_WIDTH,
              Y_CENTER_HIGH_SCORE, X_CENTER_HIGH_SCORE);
  init_window(&windows->level, LEVEL_HEIGHT, LEVEL_WIDTH, Y_CENTER_LEVEL,
              X_CENTER_LEVEL);
  init_window(&windows->start, START_HEIGHT, START_WIDTH, Y_CENTER_START,
              X_CENTER_START);
  init_window(&windows->info, INFO_HEIGHT, INFO_WIDTH, Y_CENTER_INFO,
              X_CENTER_INFO);
  init_window(&windows->game_over, START_HEIGHT, START_WIDTH, Y_CENTER_START,
              X_CENTER_START);
}

void destroy_windows(Windows_t *windows) {
  if (windows) {
    destroy_window(&windows->field);
    destroy_window(&windows->next);
    destroy_window(&windows->score);
    destroy_window(&windows->high_score);
    destroy_window(&windows->start);
    destroy_window(&windows->game_over);
    destroy_window(&windows->info);
    destroy_window(&windows->level);
  }
  endwin();
}

void resize_windows(Windows_t *windows, int *lines, int *cols) {
  if (*lines != LINES || *cols != COLS) {
    destroy_windows(windows);
    clear();
    init_windows(windows);
    *lines = LINES;
    *cols = COLS;
  }
}

void get_input(UserAction_t *action, bool *hold) {
  *hold = false;

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
    case KEY_UP:
      *action = Up;
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
      *action = None;
      break;
  }
}

static void init_window(window_t *window, int height, int width, int y, int x) {
  if (!window) {
    MEM_ALLOC_ERROR;
  }
  window->height = height;
  window->width = width;
  window->y = y;
  window->x = x;
  window->w = newwin(window->height, window->width, window->y, window->x);
}

static void destroy_window(window_t *window) {
  if (window && window->w) {
    delwin(window->w);
    window->w = NULL;
  }
}
