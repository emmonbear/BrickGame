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

#ifndef SRC_WRAPPERS_TETRIS_MODEL_H_
#define SRC_WRAPPERS_TETRIS_MODEL_H_

#include "../../interfaces/IModel.h"

extern "C" {
#include "../../brick_game/tetris/include/init.h"
#include "../../brick_game/tetris/include/model.h"
}

namespace s21 {
class TetrisModel : public IModel {
 public:
  TetrisModel();
  ~TetrisModel() override;
  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;

 private:
  Model_t *model;
};
}  // namespace s21

#endif  // SRC_WRAPPERS_TETRIS_MODEL_H_
