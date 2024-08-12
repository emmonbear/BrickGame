/**
 * @file controller.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TETRIS_CONTROLLER_H
#define TETRIS_CONTROLLER_H

#include "../../../brick_game/tetris/include/checks.h"
#include "../../../brick_game/tetris/include/figures.h"
#include "../../../brick_game/tetris/include/init.h"
#include "../../../brick_game/tetris/include/model.h"
#include "../../../brick_game/tetris/include/operations.h"
#include "../../../gui/cli/include/field_view.h"
#include "../../../gui/cli/include/init_view.h"
#include "../../../gui/cli/include/view.h"

/**
 * @brief Enumeration of user actions
 *
 * @details
 *
 * This enumeration represents all possible actions that a user can take while
 * playing the game. These actions include starting the game, pausing the game,
 * terminating the game, moving the current block left, moving the current block
 * right, rotating the current block clockwise, moving the current block down,
 * and performing an "action" (such as triggering a hard drop or activating a
 * special ability).
 */
typedef enum {
  Start,      ///< Start the game
  Pause,      ///< Pause the game
  Terminate,  ///< Terminate the game
  Left,       ///< Move the current tetromino to the left
  Right,      ///< Move the current tetromino to the right
  Up,         ///< is not used in this project
  Down,       ///< Move the current tetromino down
  Action,     ///< rotate the current tetromino
  None
} UserAction_t;

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
  Model_t model;
  View_t view;
  UserAction_t action;
  stage_t stage;
  int timer;
  bool game_over;
} Controller_t;

typedef void (*func_ptr)(Controller_t *controller);
void run_state(Controller_t *controller);
Controller_t *init_controller();
void game_loop(Controller_t *controller);
void destroy_controller(Controller_t *controller);
int get_current_time();

#endif  // TETRIS_CONTROLLER_H
