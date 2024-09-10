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

#ifndef SRC_INCLUDE_WRAPPERS_TETRIS_MODEL_H_
#define SRC_INCLUDE_WRAPPERS_TETRIS_MODEL_H_

#include "../interfaces/IModel.h"

extern "C" {
#include "../tetris/model.h"
}

namespace s21 {
class TetrisModel : public IModel {
 public:
  TetrisModel();
  ~TetrisModel() override;
  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;
  stage_t stage() override;
  bool game_over() override;

 private:
  Model_t *model_;
};
}  // namespace s21

#endif  // SRC_INCLUDE_WRAPPERS_TETRIS_MODEL_H_
