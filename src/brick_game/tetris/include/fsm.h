/**
 * @file fsm.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_BRICK_GAME_TETRIS_INCLUDE_FSM_H_
#define SRC_BRICK_GAME_TETRIS_INCLUDE_FSM_H_

#include <stdbool.h>

#include "../../../common/include/enums.h"
#include "../../../common/include/types.h"
#include "../include/checks.h"
#include "../include/figures.h"
#include "../include/model.h"
#include "../include/operations.h"

void userInput(UserAction_t action, bool hold);
void init_model();
void destroy_model();
void reset_game_info();

#endif  // SRC_BRICK_GAME_TETRIS_INCLUDE_FSM_H_
