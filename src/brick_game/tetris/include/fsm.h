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
 * @brief Realization of "START" state of finite state automaton
 *
 * @param[out] s Main structure
 */
void start_stage(singleton *s);

/**
 * @brief Realization of "SPAWN" state of finite state automaton
 *
 * @param[out] s Main structure
 */
void spawn_stage(singleton *s);

/**
 * @brief Realization of "SHIFTING" state of finite state automaton
 *
 * @param[out] s Main structure
 */
void shifting_stage(singleton *s);

/**
 * @brief Realization of "MOVING" state of finite state automaton
 *
 * @param[out] s Main structure
 */
void moving_stage(singleton *s);

/**
 * @brief Realization of "PAUSE" state of finite state automaton
 *
 * @param[out] s Main structure
 */
void pause_stage(singleton *s);

/**
 * @brief Realization of "ATTACHING" state of finite state automaton
 *
 * @param[out] s Main structure
 */
void attaching_stage(singleton *s);

/**
 * @brief Realization of "GAME_OVER" state of finite state automaton
 *
 * @param[out] s Main structure
 */
void game_over_stage(singleton *s);

#endif  // MODULES_FSM_H