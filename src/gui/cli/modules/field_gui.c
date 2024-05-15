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

#include "../include/field_gui.h"

#include <string.h>

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

void draw_field(int **field, WINDOW *w) {
  box(w, 0, 0);
  for (size_t i = 0; i < HEIGHT; i++) {
    wmove(w, i + 1, 1);
    for (size_t j = 0; j < WIDTH; j++) {
      set_color_figure(w, field[i][j]);
      waddch(w, '[');
      waddch(w, ']');
      wstandend(w);
    }
  }
  wrefresh(w);
}

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
      waddch(w, '[');
      waddch(w, ']');
      wstandend(w);
    }
  }
  wrefresh(w);
}

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

void draw_start_screen(WINDOW *w) {
  box(w, 0, 0);
  wattron(w, A_BOLD | COLOR_PAIR(4));
  mvwprintw(w, 1, 3, "  _______ ______ _______ _____  _____  _____ ");
  mvwprintw(w, 2, 3, " |__   __|  ____|__   __|  __ \\|_   _|/ ____|");
  mvwprintw(w, 3, 3, "    | |  | |__     | |  | |__) | | | | (___  ");
  mvwprintw(w, 4, 3, "    | |  |  __|    | |  |  _  /  | |  \\___ \\ ");
  mvwprintw(w, 5, 3, "    | |  | |____   | |  | | \\ \\ _| |_ ____) |");
  mvwprintw(w, 6, 3, "    |_|  |______|  |_|  |_|  \\_\\_____|_____/ ");

  wstandend(w);

  wattron(w, A_BOLD | A_BLINK);
  mvwprintw(w, 11, 17, "please, press");
  wstandend(w);

  wattron(w, A_BOLD | A_BLINK | COLOR_PAIR(5));
  mvwprintw(w, 11, 31, "ENTER");
  wstandend(w);

  mvwprintw(w, 20, 17, "powered by ");
  wattron(w, A_BOLD | COLOR_PAIR(2));

  mvwprintw(w, 20, 28, "emmonbea");
  wstandend(w);

  // int start_y = (LINES - 1) / 2;

  wrefresh(w);
}

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
