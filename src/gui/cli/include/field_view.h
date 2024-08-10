/**
 * @file field_gui.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GUI_FIELD_H
#define GUI_FIELD_H

#include "./view.h"

void draw_field(int **field, WINDOW *w);
void draw_next(int **next, WINDOW *w);
void draw_score(int score, WINDOW *w);
void draw_level(int level, WINDOW *w);
void draw_high_score(int high_score, WINDOW *w);
void draw_start_screen(WINDOW *w);
void draw_info(WINDOW *w);
void draw_pause();
void draw_game_over(WINDOW *w, int score, int high_score);
void resize_windows(View_t *view, int *lines, int *cols);

#endif  // GUI_FIELD_H
