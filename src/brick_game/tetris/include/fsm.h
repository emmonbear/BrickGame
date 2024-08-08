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

#include "./model.h"
#include "./checks.h"
#include "./figures.h"
#include "./init.h"
#include "./operations.h"

Game_t *get_instance();

/**
 * @brief Type definition for a pointer to a function that takes a Game_t
 * structure as an argument and returns nothing.
 *
 * @details
 *
 * This type definition is used to declare an array of function pointers for
 * the state machine's states. Each function pointer points to a function that
 * handles a specific state of the game. The function takes a Game_t
 * structure as an argument and performs actions based on the current state of
 * the game.
 */
typedef void (*func_ptr)(Game_t *s);

void start_stage(Game_t *s);
void spawn_stage(Game_t *s);
void shifting_stage(Game_t *s);
void moving_stage(Game_t *s);
void pause_stage(Game_t *s);
void attaching_stage(Game_t *s);
void game_over_stage(Game_t *s);
void run_state(Game_t *s);

#endif  // MODULES_FSM_H