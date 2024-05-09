/**
 * @file fsm.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_FSM_H
#define MODULES_FSM_H

#include "./backend.h"

/// @brief Number of states of a finite state machine
#define NUM_STAGES 7

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

/**
 * @brief Type definition for a pointer to a function that takes a singleton
 * structure as an argument and returns nothing.
 *
 * This type definition is used to declare an array of function pointers for
 * the state machine's states. Each function pointer points to a function that
 * handles a specific state of the game. The function takes a singleton
 * structure as an argument and performs actions based on the current state of
 * the game.
 */
typedef void (*func_ptr)(singleton *s);

/**
 * @brief Handles the start state of the game's state machine.
 *
 * This function initializes the game's data structures and sets the game's
 * state to the spawn state. It is called by the run_state function when the
 * game's state machine is in the start state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void start_stage(singleton *s);

/**
 * @brief Handles the spawn state of the game's state machine.
 *
 * This function creates a new block and selects the next block to be spawned.
 * It is called by the run_state function when the game's state machine is in
 * the spawn state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void spawn_stage(singleton *s);

/**
 * @brief Handles the shifting state of the game's state machine.
 *
 * This function moves the current block down one level after the timer expires.
 * It is called by the run_state function when the game's state machine is in
 * the shifting state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void shifting_stage(singleton *s);

/**
 * @brief Handles the moving state of the game's state machine.
 *
 * This function processes user input to rotate blocks and move blocks horizontally.
 * It is called by the run_state function when the game's state machine is in
 * the moving state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void moving_stage(singleton *s);

/**
 * @brief Handles the pause state of the game's state machine.
 *
 * This function pauses the game and waits for the user to resume or quit.
 * It is called by the run_state function when the game's state machine is in
 * the pause state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void pause_stage(singleton *s);

/**
 * @brief Handles the attaching state of the game's state machine.
 *
 * This function is called by the run_state function when the game's state
 * machine is in the attaching state. In this state, the current block is
 * attached to the already fallen blocks or the ground. If a filled line is
 * formed, it is destroyed and the remaining blocks are shifted down. If a
 * block is stopped in the topmost row, the game goes to the game over state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void attaching_stage(singleton *s);

/**
 * @brief Handles the game over state of the game's state machine.
 *
 * This function is called by the run_state function when the game's state
 * machine is in the game over state. In this state, the game is ended and
 * the player is shown the final score and game statistics.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void game_over_stage(singleton *s);

/**
 * @brief Runs the current state of the game's state machine.
 *
 * This function uses an array of function pointers to call the appropriate
 * function for the current state of the game. The function takes a singleton
 * structure as an argument and invokes the function corresponding to the
 * current state of the game.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void run_state(singleton *s) {
  static func_ptr state_funcs[NUM_STAGES] = {
    start_stage,
    spawn_stage,
    shifting_stage,
    moving_stage,
    pause_stage,
    attaching_stage,
    game_over_stage
  };

  state_funcs[s->stage](s);
}
#endif  // MODULES_FSM_H