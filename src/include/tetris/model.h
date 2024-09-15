/**
 * @file fsm.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_TETRIS_MODEL_H_
#define SRC_INCLUDE_TETRIS_MODEL_H_

#include "./figures.h"
#include "./operations.h"
#include "./types.h"

void init_model();
void destroy_model();
void init_game_info();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
stage_t stage();
bool game_over();
Model_t get_model();
void set_model_stage(stage_t stage);
void set_model(Model_t model_);
void set_game_info(GameInfo_t game_info_);

#endif  // SRC_INCLUDE_TETRIS_MODEL_H_
