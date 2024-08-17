/**
 * @file settings.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_GUI_CLI_INCLUDE_SETTINGS_H_
#define SRC_GUI_CLI_INCLUDE_SETTINGS_H_

/// @brief Number of lines on Field
#define HEIGHT 20

/// @brief Number of columns on Field
#define WIDTH 10

/// @brief The size of the tetromino
#define TETROMINO_SIZE 4

/// @brief Size of border
#define BORDER_SIZE 2

/// @brief Cell size
#define CELL_SIZE 2

//  FIELD
/// @brief Width of the playing field including borders and cell size
#define FIELD_WIDTH (WIDTH * CELL_SIZE) + BORDER_SIZE

/// @brief Height of the playing field including borders
#define FIELD_HEIGHT HEIGHT + BORDER_SIZE

/// @brief Y coordinate of the playing field
#define Y_CENTER_FIELD (LINES - HEIGHT) / 2

/// @brief X coordinate of the playing field
#define X_CENTER_FIELD ((COLS - WIDTH) / 2)

//  NEXT
/// @brief WIDTH of the "NEXT" window including borders and cell size
#define NEXT_WIDTH (TETROMINO_SIZE * CELL_SIZE) + (BORDER_SIZE) + (2)

/// @brief Height of the "NEXT" window including borders and caption size
#define NEXT_HEIGHT (TETROMINO_SIZE) + (BORDER_SIZE) + (4)

/// @brief Y coordinate for the "NEXT" window
#define Y_CENTER_NEXT (Y_CENTER_FIELD + FIELD_HEIGHT) - (NEXT_HEIGHT)

/// @brief X coordinate for the "NEXT" window
#define X_CENTER_NEXT X_CENTER_FIELD + FIELD_WIDTH

//  SCORE
/// @brief WIDTH of the "SCORE" window
#define SCORE_WIDTH NEXT_WIDTH

/// @brief HEIGHT of the "SCORE" window
#define SCORE_HEIGHT (TETROMINO_SIZE)

/// @brief Y coordinate for the "SCORE" window
#define Y_CENTER_SCORE (Y_CENTER_NEXT) - (SCORE_HEIGHT)

/// @brief X coordinate for the "SCORE" window
#define X_CENTER_SCORE X_CENTER_NEXT

//  LEVEL
/// @brief WIDTH of the "LEVEL" window
#define LEVEL_WIDTH SCORE_WIDTH

/// @brief HEIGHT of the "LEVEL" window
#define LEVEL_HEIGHT SCORE_HEIGHT

/// @brief Y coordinate for the "LEVEL" window
#define Y_CENTER_LEVEL (Y_CENTER_SCORE) - (LEVEL_HEIGHT)

/// @brief X coordinate for the "LEVEL" window
#define X_CENTER_LEVEL (X_CENTER_SCORE)

//  HIGH_SCORE
/// @brief WIDTH of the "HIGH_SCORE" window
#define HIGH_SCORE_WIDTH LEVEL_WIDTH

/// @brief HEIGHT of the "HIGH_SCORE" window
#define HIGH_SCORE_HEIGHT (LEVEL_HEIGHT)

/// @brief Y coordinate for the "HIGH_SCORE" window
#define Y_CENTER_HIGH_SCORE (Y_CENTER_LEVEL) - (HIGH_SCORE_HEIGHT)

/// @brief X coordinate for the "HIGH_SCORE" window
#define X_CENTER_HIGH_SCORE (X_CENTER_LEVEL)

//  START
/// @brief HEIGHT of the "START" window
#define START_HEIGHT FIELD_HEIGHT

/// @brief WIDTH of the "START" window
#define START_WIDTH (FIELD_WIDTH) + (NEXT_WIDTH) + (INFO_WIDTH)

/// @brief Y coordinate for the "START" window
#define Y_CENTER_START Y_CENTER_FIELD

/// @brief X coordinate for the "START" window
#define X_CENTER_START (X_CENTER_FIELD) - (INFO_WIDTH)

// INFO
/// @brief HEIGHT of the "INFO" window
#define INFO_HEIGHT (FIELD_HEIGHT)

/// @brief WIDTH of the "INFO" window
#define INFO_WIDTH (NEXT_WIDTH) * 1.5

/// @brief Y coordinate for the "INFO" window
#define Y_CENTER_INFO (Y_CENTER_FIELD)

/// @brief X coordinate for the "INFO" window
#define X_CENTER_INFO (X_CENTER_FIELD) - (INFO_WIDTH)

/// @brief Y coordinate for the "PAUSE"
#define Y_CENTER_PAUSE (Y_CENTER_FIELD)

/// @brief X coordinate for the "PAUSE"
#define X_CENTER_PAUSE ((X_CENTER_FIELD) - (INFO_WIDTH))

#endif  // SRC_GUI_CLI_INCLUDE_SETTINGS_H_
