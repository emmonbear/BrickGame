/**
 * @file common_gui.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Tetris View header
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GUI_COMMON_H
#define GUI_COMMON_H

#include <ncurses.h>

#include "../../../controller/tetris/include/controller.h"
#include "./settings.h"

/**
 * @brief Structure representing a window in the game.
 *
 * @details This structure contains information about the size, position, and
 * window pointer for a particular game window.
 *
 */
typedef struct {
  int height;  ///< The height of the window.
  int width;   ///< The width of the window.
  int y;       ///< The y-coordinate of the window's position on the screen.
  int x;       ///< The x-coordinate of the window's position on the screen.
  WINDOW *w;   ///< A pointer to the `WINDOW` structure used by the ncurses
               /// library.
} window_t;

/**
 * @brief Structure representing various windows in the game's view.
 *
 * @details This structure contains information about different windows used to
 * display the game state, including the game field, next tetromino, score, high
 * score, level, start screen, additional information, and game over screen.
 */
typedef struct {
  window_t field;       ///< Window for displaying the game field.
  window_t next;        ///< Window for displaying the next tetromino.
  window_t score;       ///< Window for displaying the current score.
  window_t high_score;  ///< Window for displaying the high score.
  window_t level;       ///< Window for displaying the current level.
  window_t start;       ///< Window for displaying the start screen.
  window_t info;        ///< Window for displaying additional game information.
  window_t game_over;   ///< Window for displaying the game over screen.
} Windows_t;

typedef struct {
  Windows_t windows;
  Controller_t controller;
} View_t;

void init_screen();
View_t *init_view();
void init_windows(Windows_t *windows);
void destroy_view(View_t *view);
void resize_windows(Windows_t *windows, int *lines, int *cols);
void game_loop(View_t *view);

#endif  // GUI_COMMON_H
