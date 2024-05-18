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

#include "./common_gui.h"

/**
 * @brief Draws the game field on the screen.
 * @param[in] field A pointer to the game field's matrix.
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_field(int **field, WINDOW *w);

/**
 * @brief Draws the next tetromino on the screen.
 *
 * @param[in] next A pointer to the game field's matrix.
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_next(int **next, WINDOW *w);

/**
 * @brief Draws the score window on the screen
 *
 * @param[in] score Current game score
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_score(int score, WINDOW *w);

/**
 * @brief Draws the level window on the screen
 *
 * @param[in] level Current game level
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_level(int level, WINDOW *w);

/**
 * @brief Draws the high score window on the screen
 *
 * @param[in] high_score Current game high score
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_high_score(int high_score, WINDOW *w);

/**
 * @brief Draws start window on the screen
 *
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_start_screen(WINDOW *w);

/**
 * @brief Draws info window on the screen
 *
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 */
void draw_info(WINDOW *w);

/**
 * @brief Draws pause on the screen
 *
 */
void draw_pause();

/**
 * @brief Draws game over window on the screen
 *
 * @param[in] w A pointer to the ncurses window where the game field will be
 * drawn.
 * @param[in] score Game score
 * @param[in] high_score Game high score
 */
void draw_game_over(WINDOW *w, int score, int high_score);

#endif  // GUI_FIELD_H