/**
 * @file init_gui.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/init_gui.h"

#include <stdlib.h>

static void init_window(window_t *w, int height, int width, int y, int x);

void init_screen() {
  initscr();
  raw();
  nodelay(stdscr, TRUE);
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  start_color();
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

windows *init_windows() {
  windows *wins = (windows *)malloc(sizeof(windows));

  if (wins) {
    init_window(&wins->field, FIELD_HEIGHT, FIELD_WIDTH, Y_CENTER_FIELD,
                X_CENTER_FIELD);
    init_window(&wins->next, NEXT_HEIGHT, NEXT_WIDTH, Y_CENTER_NEXT,
                X_CENTER_NEXT);
    init_window(&wins->score, SCORE_HEIGHT, SCORE_WIDTH, Y_CENTER_SCORE,
                X_CENTER_SCORE);
    init_window(&wins->high_score, HIGH_SCORE_HEIGHT, HIGH_SCORE_WIDTH,
                Y_CENTER_HIGH_SCORE, X_CENTER_HIGH_SCORE);
    init_window(&wins->level, LEVEL_HEIGHT, LEVEL_WIDTH, Y_CENTER_LEVEL,
                X_CENTER_LEVEL);
    init_window(&wins->start, START_HEIGHT, START_WIDTH, Y_CENTER_START,
                X_CENTER_START);
    init_window(&(wins->info), INFO_HEIGHT, INFO_WIDTH, Y_CENTER_INFO,
                X_CENTER_INFO);
    init_window(&(wins->game_over), START_HEIGHT, START_WIDTH, Y_CENTER_START,
                X_CENTER_START);
  }

  return wins;
}

void destroy_windows(windows **wins) {
  if (*wins) {
    delwin((*wins)->field.w);
    delwin((*wins)->next.w);
    delwin((*wins)->score.w);
    delwin((*wins)->high_score.w);
    delwin((*wins)->level.w);
    delwin((*wins)->start.w);
    delwin((*wins)->info.w);
    delwin((*wins)->game_over.w);
    free(*wins);
  }
}

static void init_window(window_t *w, int height, int width, int y, int x) {
  w->height = height;
  w->width = width;
  w->y = y;
  w->x = x;
  w->w = newwin(w->height, w->width, w->y, w->x);
}

void update_windows(windows **wins, int *lines, int *cols) {
  if (*lines != LINES || *cols != COLS) {
    destroy_windows(wins);
    clear();
    *wins = init_windows();
    *lines = LINES;
    *cols = COLS;
  }
}