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

#include "../include/common_module.h"
#include "./checks.h"
#include "./figures.h"
#include "./init.h"
#include "./operations.h"

singleton *get_instance();

/**
 * @brief Type definition for a pointer to a function that takes a singleton
 * structure as an argument and returns nothing.
 *
 * @details
 *
 * This type definition is used to declare an array of function pointers for
 * the state machine's states. Each function pointer points to a function that
 * handles a specific state of the game. The function takes a singleton
 * structure as an argument and performs actions based on the current state of
 * the game.
 */
typedef void (*func_ptr)(singleton *s);

void start_stage(singleton *s);
void spawn_stage(singleton *s);
void shifting_stage(singleton *s);
void moving_stage(singleton *s);
void pause_stage(singleton *s);
void attaching_stage(singleton *s);
void game_over_stage(singleton *s);
void run_state(singleton *s);

#endif  // MODULES_FSM_H