/**
 * @file common.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_COMMON_H
#define MODULES_COMMON_H

#include "../../../common.h"

/// @brief Number of states of a finite state machine
#define NUM_STAGES 7

#define MAX_LEVEL 10

#define SCORE_PER_LEVEL 600

/// @brief Enumeration of states of a Finite-state machine
typedef enum {
  START,  ///< the state in which the game waits for the player to press the
          ///< ready to play button
  SPAWN,  ///< the state the game switches to when creating the next block and
          ///< selecting the next block to be spawned
  SHIFTING,   ///< the state to which the game switches after the timer expires.
              ///< In this state the current block moves down one level
  MOVING,     ///< basic game state with user input processing - rotating
              ///< blocks/moving blocks horizontally
  PAUSE,      ///< the state in which the game is paused
  ATTACHING,  ///< the state the game goes to after the current block "touches"
              ///< the already fallen blocks or the ground. If a filled line is
              ///< formed, it is destroyed and the remaining blocks are shifted
              ///< down. If a block is stopped in the topmost row, the game goes
              ///< to the state "game over"
  GAME_OVER,  ///< the state that characterizes the end of the game
} stage_t;

typedef struct {
  int **field;  ///< 2D array representing the game field, where each element
                ///< corresponds to a cell on the field. The value of an element
                ///< is either 0 (empty cell) or a positive integer (cell
                ///< occupied by a block, with the value indicating the color of
                ///< the block).
  int **next;   ///< 2D array representing the next block to be spawned.
  int score;    ///< The current score of the player.
  int high_score;  ///< The highest score achieved by any player.
  int level;  ///< The current level of the game, which determines the speed at
              ///< which blocks fall.
  int speed;  ///< The speed at which blocks fall, measured in milliseconds
              ///< between each downward movement.
  int pause;  ///< A flag indicating whether the game is currently paused (1) or
              ///< not (0).
} GameInfo_t;

/// @brief Enumeration representing the different types of tetrominoes in the
/// game.
typedef enum {
  TET_I,  ///< The "I" shaped tetromino, consisting of four blocks in a straight
          ///< line.
  TET_Z,  ///< The "Z" shaped tetromino, consisting of three blocks in a zigzag
          ///< pattern and one block on the side.
  TET_S,  ///< The "S" shaped tetromino, consisting of three blocks in a zigzag
          ///< pattern and one block on the opposite side.
  TET_T,  ///< The "T" shaped tetromino, consisting of three blocks in a
          ///< straight line and one block perpendicular to the middle block.
  TET_L,  ///< The "L" shaped tetromino, consisting of three blocks in a
          ///< straight line and one block perpendicular to the end block.
  TET_J,  ///< The "J" shaped tetromino, consisting of three blocks in a
          ///< straight line and one block perpendicular to the opposite end
          ///< block.
  TET_O,  ///< The "O" shaped tetromino, consisting of four blocks arranged in a
          ///< 2x2 square.
} type_t;

/**
 * @brief Struct representing a tetromino figure in the game.
 *
 * This structure contains information about the current and next tetromino
 * shapes, their types, colors, coordinates of the current figure and
 * two-dimensional arrays representing the inverted figure and the current
 * figure
 */
typedef struct {
  type_t next_type;     ///< The type of the next tetromino figure.
  type_t current_type;  ///< The type of the current tetromino figure.
  int x, y;             ///< The x and y coordinates of the top left corner of
                        ///< the current tetromino figure on the game board.
  int rotation;         ///< The rotation index of the current tetromino figure.
  int next_color;       ///< The color index of the next tetromino figure.
  int current_color;    ///< The color index of the current tetromino figure.
  int **current_figure;  ///< A 2D array representing the shape of the current
                         ///< tetromino figure.
  int **rotated_figure;  ///< A 2D array representing the shape of the current
                         ///< tetromino figure after rotation.
} figure_t;

typedef struct {
  GameInfo_t *game_info;
  stage_t stage;
  figure_t figure;
  UserAction_t *action;
  int timer;
  int game_over;
} singleton;

#endif  // MODULES_COMMON_H