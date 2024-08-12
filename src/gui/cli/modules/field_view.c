/**
 * @file field_gui.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/field_view.h"

#include <string.h>

#include "../include/init_view.h"

static void set_color_figure(WINDOW *w, int color_index) {
  switch (color_index) {
    case 0:
      wattron(w, COLOR_PAIR(0) | A_DIM);
      break;
    case 1:
      wattron(w, COLOR_PAIR(1) | A_BOLD);
      break;
    case 2:
      wattron(w, COLOR_PAIR(2) | A_BOLD);
      break;
    case 3:
      wattron(w, COLOR_PAIR(3) | A_BOLD);
      break;
    case 4:
      wattron(w, COLOR_PAIR(4) | A_BOLD);
      break;
    case 5:
      wattron(w, COLOR_PAIR(5) | A_BOLD);
      break;
    case 6:
      wattron(w, COLOR_PAIR(6) | A_BOLD);
      break;
    case 7:
      wattron(w, COLOR_PAIR(7) | A_BOLD);
      break;
  }
}

/**
 * @brief Draws the game field on the screen.
 * @param[in] field A pointer to the game field's matrix.
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_field(int **field, WINDOW *w) {
  box(w, 0, 0);
  for (size_t i = 0; i < HEIGHT; i++) {
    wmove(w, i + 1, 1);
    for (size_t j = 0; j < WIDTH; j++) {
      if (field[i][j] == 0) {
        waddch(w, ' ');
        waddch(w, ' ');
        wstandend(w);
      } else {
        set_color_figure(w, field[i][j]);
        waddch(w, '[');
        waddch(w, ']');
        wstandend(w);
      }
    }
  }
  wrefresh(w);
}

/**
 * @brief Draws the next tetromino on the screen.
 *
 * @param[in] next A pointer to the game field's matrix.
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_next(int **next, WINDOW *w) {
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

  wattron(w, A_BOLD);
  mvwprintw(w, 1, center_x, "NEXT");
  wstandend(w);

  for (int i = 0; i < TETROMINO_SIZE; i++) {
    wmove(w, i + 3, 2);
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      set_color_figure(w, next[i][j]);
      if (next[i][j] == 0) {
        waddch(w, ' ');
        waddch(w, ' ');
        wstandend(w);
      } else {
        waddch(w, '[');
        waddch(w, ']');
        wstandend(w);
      }
    }
  }
  wrefresh(w);
}

/**
 * @brief Draws the score window on the screen
 *
 * @param[in] score Current game score
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_score(int score, WINDOW *w) {
  box(w, 0, 0);
  int center_x_1 = (SCORE_WIDTH - strlen("SCORE")) / 2;
  char score_str[16];
  snprintf(score_str, sizeof(score_str), "%d", score);

  int center_x_2 = (SCORE_WIDTH - strlen(score_str)) / 2;

  wattron(w, A_BOLD);
  mvwprintw(w, 1, center_x_1, "SCORE");
  mvwprintw(w, 2, center_x_2, "%s", score_str);
  wstandend(w);
  wrefresh(w);
}

/**
 * @brief Draws the level window on the screen
 *
 * @param[in] level Current game level
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_level(int level, WINDOW *w) {
  box(w, 0, 0);
  int center_x_1 = (LEVEL_WIDTH - strlen("LEVEL")) / 2;
  char level_str[16];
  snprintf(level_str, sizeof(level_str), "%d", level);
  int center_x_2 = (LEVEL_WIDTH - strlen(level_str)) / 2;

  wattron(w, A_BOLD);
  mvwprintw(w, 1, center_x_1, "LEVEL");
  mvwprintw(w, 2, center_x_2, "%s", level_str);
  wstandend(w);
  wrefresh(w);
}

/**
 * @brief Draws the high score window on the screen
 *
 * @param[in] high_score Current game high score
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_high_score(int high_score, WINDOW *w) {
  box(w, 0, 0);
  int center_x_1 = (LEVEL_WIDTH - strlen("HIGH SCORE")) / 2;
  char high_score_str[16];
  snprintf(high_score_str, sizeof(high_score_str), "%d", high_score);
  int center_x_2 = (LEVEL_WIDTH - strlen(high_score_str)) / 2;

  wattron(w, A_BOLD);
  mvwprintw(w, 1, center_x_1, "HIGH SCORE");
  mvwprintw(w, 2, center_x_2, "%s", high_score_str);
  wstandend(w);
  wrefresh(w);
}

/**
 * @brief Draws start window on the screen
 *
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_start_screen(WINDOW *w) {
  box(w, 0, 0);
  wattron(w, A_BOLD | COLOR_PAIR(4));
  mvwprintw(w, 1, 5, "   ___      _     __   _____  ");
  mvwprintw(w, 2, 5, "  / _ )____(_)___/ /__/ ___/__ ___ _  ___");
  mvwprintw(w, 3, 5, " / _  / __/ / __/  '_/ (_ / _ `/  ' \\/ -_)");
  mvwprintw(w, 4, 5, "/____/_/ /_/\\__/_/\\_\\\\___/\\_,_/_/_/_/\\__/");

  wstandend(w);

  wattron(w, A_BOLD | A_BLINK);
  mvwprintw(w, 11, 17, "please, press");
  wstandend(w);

  wattron(w, A_BOLD | A_BLINK | COLOR_PAIR(5));
  mvwprintw(w, 11, 31, "ENTER");
  wstandend(w);

  mvwprintw(w, 20, 17, "designed by ");
  wattron(w, A_BOLD | COLOR_PAIR(2));

  mvwprintw(w, 20, 29, "emmonbea");
  wstandend(w);

  wrefresh(w);
}

/**
 * @brief Draws info window on the screen
 *
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_info(WINDOW *w) {
  box(w, 0, 0);
  int center_x_1 = (INFO_WIDTH - strlen("INFO")) / 2;
  wattron(w, A_BOLD);
  mvwprintw(w, 1, center_x_1, "INFO");
  mvwprintw(w, 3, 3, "Left");
  mvwaddch(w, 3, 12, ACS_LARROW);
  mvwprintw(w, 5, 3, "Right");
  mvwaddch(w, 5, 12, ACS_RARROW);
  mvwprintw(w, 7, 3, "Down");
  mvwaddch(w, 7, 12, ACS_DARROW);
  mvwprintw(w, 9, 3, "Pause");
  mvwaddch(w, 9, 12, 'p');
  mvwprintw(w, 11, 3, "Action");
  mvwprintw(w, 11, 10, "Space");
  mvwprintw(w, 13, 3, "Exit");
  mvwaddch(w, 13, 12, 'q');

  wstandend(w);

  wrefresh(w);
}

/**
 * @brief Draws pause on the screen
 *
 */
void draw_pause() {
  attron(A_BOLD | A_BLINK | COLOR_PAIR(5));

  mvprintw((Y_CENTER_PAUSE) + 7, (X_CENTER_PAUSE) + 8,
           "  _____       _    _  _____ ______ ");
  mvprintw((Y_CENTER_PAUSE) + 8, (X_CENTER_PAUSE) + 8,
           " |  __ \\ /\\  | |  | |/ ____|  ____|");
  mvprintw((Y_CENTER_PAUSE) + 9, (X_CENTER_PAUSE) + 8,
           " | |__) /  \\ | |  | | (___ | |__   ");
  mvprintw((Y_CENTER_PAUSE) + 10, (X_CENTER_PAUSE) + 8,
           " |  ___/ /\\ \\| |  | |\\___ \\|  __| ");
  mvprintw((Y_CENTER_PAUSE) + 11, (X_CENTER_PAUSE) + 8,
           " | |  / ____ \\ |__| |____) | |____ ");
  mvprintw((Y_CENTER_PAUSE) + 12, (X_CENTER_PAUSE) + 8,
           " |_| /_/    \\_\\____/|_____/|______|");

  standend();
}

/**
 * @brief Draws game over window on the screen
 *
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 * @param[in] score Game score
 * @param[in] high_score Game high score
 */
void draw_game_over(WINDOW *w, int score, int high_score) {
  box(w, 0, 0);
  wattron(w, A_BOLD | COLOR_PAIR(4));

  mvwprintw(w, 1, 9, "   _____          __  __ ______ ");
  mvwprintw(w, 2, 9, "  / ____|   /\\   |  \\/  |  ____|");
  mvwprintw(w, 3, 9, " | |  __   /  \\  | \\  / | |__  ");
  mvwprintw(w, 4, 9, " | | |_ | / /\\ \\ | |\\/| |  __|");
  mvwprintw(w, 5, 9, " | |__| |/ ____ \\| |  | | |____ ");
  mvwprintw(w, 6, 9, "  \\_____/_/    \\_\\_|  |_|______|");

  mvwprintw(w, 7, 10, "   ______      ________ _____");
  mvwprintw(w, 8, 10, "  / __ \\ \\    / /  ____|  __ \\");
  mvwprintw(w, 9, 10, " | |  | \\ \\  / /| |__  | |__) |");
  mvwprintw(w, 10, 10, " | |  | |\\ \\/ / |  __| |  _  / ");
  mvwprintw(w, 11, 10, " | |__| | \\  /  | |____| | \\ \\ ");
  mvwprintw(w, 12, 10, "  \\____/   \\/   |______|_|  \\_\\");
  wstandend(w);

  wattron(w, A_BOLD);
  mvwprintw(w, 15, 17, "     SCORE = %d", score);
  mvwprintw(w, 16, 17, "HIGH_SCORE = %d", high_score);
  wstandend(w);

  wrefresh(w);
}

/**
 * @brief Updates the windows for the game.
 *
 * @details
 *
 * This function takes a pointer to a pointer to a `windows` struct and two
 * pointers to integers representing the current number of lines and columns on
 * the screen. It checks if the current number of lines and columns is different
 * from the number of lines and columns that were used to initialize the
 * windows. If the number of lines and columns has changed, the function
 * destroys the current windows using the `destroy_windows()` function, clears
 * the screen using the `clear()` function from the ncurses library, and
 * initializes new windows using the `init_windows()` function. The function
 * then updates the values of the pointers to the current number of lines and
 * columns.
 *
 * @param[in, out] wins - A pointer to a pointer to the `windows` struct to be
 * updated.
 * @param[in, out] lines - A pointer to an integer representing the current
 * number of lines on the screen.
 * @param[in, out] cols - A pointer to an integer representing the current
 * number of columns on the screen.
 */
void resize_windows(View_t *view, int *lines, int *cols) {
  if (*lines != LINES || *cols != COLS) {
    destroy_view(view);
    clear();
    init_view(view);
    *lines = LINES;
    *cols = COLS;
  }
}
