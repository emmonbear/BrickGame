/**
 * @file controller.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/controller/controller.h"

namespace s21 {
Controller::Controller(IModel *model) : model_(model) {}
Controller::~Controller() { delete model_; }

GameInfo_t Controller::updateCurrentState() {
  return model_->updateCurrentState();
}

void Controller::userInput(UserAction_t action, bool hold) {
  return model_->userInput(action, hold);
}

bool Controller::game_over() { return model_->game_over(); }
stage_t Controller::stage() { return model_->stage(); }

}  // namespace s21
