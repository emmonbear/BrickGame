/**
 * @file model.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Tetris game model header file
 * @version 1.0
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MODEL_H
#define MODEL_H

#include "../../common.h"
#include "../../../brick_game.h"

/// @brief Number of states of a finite state machine
#define NUM_STAGES 7

/// @brief Number of levels
#define MAX_LEVEL 10

/// @brief Amount of experience required to increase the level
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
  type_t next_type;      ///< The type of the next tetromino figure.
  type_t current_type;   ///< The type of the current tetromino figure.
  int x, y;              ///< The x and y coordinates of the top left corner of
                         ///< the current tetromino figure on the game board.
  int next_color;        ///< The color index of the next tetromino figure.
  int current_color;     ///< The color index of the current tetromino figure.
  int **current_figure;  ///< A 2D array representing the shape of the current
                         ///< tetromino figure.
  int **rotated_figure;  ///< A 2D array representing the shape of the current
                         ///< tetromino figure after rotation.
} figure_t;

typedef struct {
  GameInfo_t game_info;  ///< Pointer to the game's information
  stage_t stage;         ///< The current state of the game
  figure_t figure;       ///< Information about figures
  UserAction_t action;   ///< Pointer to the user's action
  int timer;             ///< Timer used to control the game's events
  int game_over;         ///< Flag that indicates if the game is over
} Game_t;

#endif  // MODEL_H

