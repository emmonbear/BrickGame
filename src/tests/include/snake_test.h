/**
 * @file snake_test.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_TESTS_INCLUDE_SNAKE_TEST_H_
#define SRC_TESTS_INCLUDE_SNAKE_TEST_H_

#include "../include/main_test.h"

namespace s21 {
class SnakeTest : public ::testing::Test {
 public:
  GameInfo_t game_info();
  bool ArrayIsEmpty(int **array, int rows, int cols);

 protected:
  void SetUp() override { game_info_ = model_.updateCurrentState(); }

 private:
  SnakeModel model_;
  GameInfo_t game_info_;
};
}  // namespace s21

#endif  // SRC_TESTS_INCLUDE_SNAKE_TEST_H_
