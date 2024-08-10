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
 * @brief Initializes the screen and sets up the colors for the game.
 *
 * @details
 * This function initializes the screen using the initscr() function from the
 * ncurses library. It also sets up the screen to be in raw mode, to not delay
 * input, to not echo input, and to enable the keypad. The function sets the
 * cursor to be invisible and starts the color system using the start_color()
 * function from the ncurses library. Finally, the function initializes the
 * color pairs using the init_pair() function from the ncurses library.
 */
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

/**
 * @brief Initializes the View_t for the game.
 *
 * @details
 * This function allocates memory for a `View_t` struct using the `malloc()`
 * function from the C standard library. It then initializes each window in the
 * struct using the `init_window()` function. The View_t include the game
 * field, the next tetromino, the score, the high score, the level, the start
 * window, the info window, and the game over window.
 *
 * @return View_t* A pointer to the initialized `View_t` struct.
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
 * @brief Destroys the windows for the game.
 *
 * @details
 * This function takes a pointer to a pointer to a `windows` struct and destroys
 * each window in the struct using the `delwin()` function from the ncurses
 * library. It then frees the memory allocated for the struct using the `free()`
 * function from the C standard library.
 *
 * @param[in,out] view - A pointer to a pointer to the `windows` struct to be
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
