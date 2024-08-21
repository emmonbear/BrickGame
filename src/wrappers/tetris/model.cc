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

#include "./model.h"

namespace s21 {
TetrisModel::TetrisModel() { init_model(model); }

TetrisModel::~TetrisModel() { destroy_model(model); }

GameInfo_t TetrisModel::updateCurrentState() { return model->game_info; }

void TetrisModel::userInput(UserAction_t action, bool hold) {
  // return userInput(UserAction_t action, bool hold);
}

}  // namespace s21
