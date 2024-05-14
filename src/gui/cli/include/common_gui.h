/**
 * @file common_gui.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GUI_COMMON_H
#define GUI_COMMON_H

#include <ncurses.h>

#include "../../../common.h"

/// @brief Size of border
#define BORDER_SIZE 2

/// @brief Cell size
#define CELL_SIZE 2

/// @brief Width of the playing field including borders and cell size
#define FIELD_WIDTH (WIDTH * CELL_SIZE) + BORDER_SIZE

/// @brief Height of the playing field including borders
#define FIELD_HEIGHT HEIGHT + BORDER_SIZE

/// @brief Y coordinate of the playing field
#define Y_CENTER_FIELD (LINES - HEIGHT) / 2

/// @brief X coordinate of the playing field
#define X_CENTER_FIELD (COLS - WIDTH) / 2

/// @brief WIDTH of the "NEXT" window including borders and cell size
#define NEXT_WIDTH (TETROMINO_SIZE * CELL_SIZE) + (BORDER_SIZE) + (2)

/// @brief Height of the "NEXT" window including borders and caption size
#define NEXT_HEIGHT (TETROMINO_SIZE) + (BORDER_SIZE) + (4)

/// @brief Y coordinate for the "NEXT" window
#define Y_CENTER_NEXT (Y_CENTER_FIELD + FIELD_HEIGHT) - (NEXT_HEIGHT)

/// @brief X coordinate for the "NEXT" window
#define X_CENTER_NEXT X_CENTER_FIELD + FIELD_WIDTH

#define SCORE_WIDTH NEXT_WIDTH

#define SCORE_HEIGHT (TETROMINO_SIZE)

#define Y_CENTER_SCORE (Y_CENTER_NEXT) - (SCORE_HEIGHT)

#define X_CENTER_SCORE X_CENTER_NEXT

#define LEVEL_WIDTH SCORE_WIDTH

#define LEVEL_HEIGHT SCORE_HEIGHT

#define Y_CENTER_LEVEL (Y_CENTER_SCORE) - (LEVEL_HEIGHT)

#define X_CENTER_LEVEL (X_CENTER_SCORE)

#define HIGH_SCORE_WIDTH LEVEL_WIDTH

#define HIGH_SCORE_HEIGHT (LEVEL_HEIGHT)

#define Y_CENTER_HIGH_SCORE (Y_CENTER_LEVEL) - (HIGH_SCORE_HEIGHT)

#define X_CENTER_HIGH_SCORE (X_CENTER_LEVEL)

#define START_HEIGHT FIELD_HEIGHT

#define START_WIDTH (FIELD_WIDTH) + (NEXT_WIDTH)

#define Y_CENTER_START Y_CENTER_FIELD

#define X_CENTER_START X_CENTER_FIELD

#endif  // GUI_COMMON_H