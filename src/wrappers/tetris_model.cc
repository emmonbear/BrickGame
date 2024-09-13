/**
 * @file model.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */

extern "C" {
#include "../include/tetris/model.h"
}

#include "../include/wrappers/tetris_model.h"

namespace s21 {
TetrisModel::TetrisModel() { ::init_model(); }

TetrisModel::~TetrisModel() { ::destroy_model(); }

GameInfo_t TetrisModel::updateCurrentState() { return ::updateCurrentState(); }

void TetrisModel::userInput(UserAction_t action, bool hold) {
  return ::userInput(action, hold);
}

stage_t TetrisModel::stage() { return ::stage(); }

bool TetrisModel::game_over() { return ::game_over(); }

}  // namespace s21
