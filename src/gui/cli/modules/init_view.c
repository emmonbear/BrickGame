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

#include "../include/init_view.h"

#include <stdlib.h>

static void init_window(window_t *w, int height, int width, int y, int x);

/**
 * @brief Initializes the terminal screen for the game.
 *
 * @details This function sets up the terminal for the game by initializing
 * ncurses mode, configuring input settings, and setting up color pairs for
 * different game elements. It ensures that the terminal is in raw mode,
 * disables echoing of typed characters, and makes the cursor invisible.
 */
void init_screen() {
  initscr();              // Initialize ncurses mode
  raw();                  // Disable line buffering
  nodelay(stdscr, TRUE);  // Set non-blocking input
  noecho();               // Disable echoing of typed characters
  keypad(stdscr, TRUE);   // Enable special keys to be read
  curs_set(0);            // Hide the cursor
  start_color();          // Enable color functionality

  // Initialize color pairs
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

/**
 * @brief Initializes the view components for the game.
 *
 * @details This function sets up the windows for different game elements
 * (field, next, score, high score, level, start screen, info, and game over) by
 * calling `init_window` for each component with the appropriate dimensions and
 * positions.
 *
 * @param view A pointer to the View_t structure that contains all the windows
 * to be initialized.
 */
void init_view(View_t *view) {
  if (view) {
    init_window(&view->field, FIELD_HEIGHT, FIELD_WIDTH, Y_CENTER_FIELD,
                X_CENTER_FIELD);
    init_window(&view->next, NEXT_HEIGHT, NEXT_WIDTH, Y_CENTER_NEXT,
                X_CENTER_NEXT);
    init_window(&view->score, SCORE_HEIGHT, SCORE_WIDTH, Y_CENTER_SCORE,
                X_CENTER_SCORE);
    init_window(&view->high_score, HIGH_SCORE_HEIGHT, HIGH_SCORE_WIDTH,
                Y_CENTER_HIGH_SCORE, X_CENTER_HIGH_SCORE);
    init_window(&view->level, LEVEL_HEIGHT, LEVEL_WIDTH, Y_CENTER_LEVEL,
                X_CENTER_LEVEL);
    init_window(&view->start, START_HEIGHT, START_WIDTH, Y_CENTER_START,
                X_CENTER_START);
    init_window(&view->info, INFO_HEIGHT, INFO_WIDTH, Y_CENTER_INFO,
                X_CENTER_INFO);
    init_window(&view->game_over, START_HEIGHT, START_WIDTH, Y_CENTER_START,
                X_CENTER_START);
  }
}

/**
 * @brief Destroys the view components of the game.
 *
 * @details This function deletes all the windows created for the different game
 * elements (field, next, score, high score, level, start screen, info, and game
 * over) by calling `delwin` for each window.
 *
 * @param view A pointer to the View_t structure containing the windows to be
 * destroyed.
 */
void destroy_view(View_t *view) {
  if (view) {
    delwin(view->field.w);
    delwin(view->next.w);
    delwin(view->score.w);
    delwin(view->high_score.w);
    delwin(view->level.w);
    delwin(view->start.w);
    delwin(view->info.w);
    delwin(view->game_over.w);
  }
}

static void init_window(window_t *w, int height, int width, int y, int x) {
  w->height = height;
  w->width = width;
  w->y = y;
  w->x = x;
  w->w = newwin(w->height, w->width, w->y, w->x);
}
