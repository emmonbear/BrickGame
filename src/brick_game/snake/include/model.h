/**
 * @file model.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_BRICK_GAME_SNAKE_INCLUDE_MODEL_H_
#define SRC_BRICK_GAME_SNAKE_INCLUDE_MODEL_H_

extern "C" {
#include "../../../common/include/common.h"
}

#include <vector>

namespace s21 {
class SnakeModel {
 public:
  SnakeModel();
  ~SnakeModel();

  void StartGame();
  void InitializeGame();
  inline const GameInfo_t &get_info() const {
    return info_;
  }

  inline const std::vector<std::pair<int, int>> &get_snake() const {
    return snake_;
  }

  inline const std::pair<int, int> &get_food() const {
    return food_;
  }

 private:
  GameInfo_t info_;
  std::vector<std::pair<int, int>> snake_;
  std::pair<int, int> food_;

  void GenerateFood();
  void UpdateField();
  void ClearField();
  void PlaceSnakeOnField();
  void PlaceFoodOnField();
};
}  // namespace s21

#endif  // SRC_BRICK_GAME_SNAKE_INCLUDE_MODEL_H_
