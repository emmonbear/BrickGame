/**
 * @file snake_model_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/snake_test.h"

namespace s21 {
bool SnakeTest::ArrayIsEmpty(int **array, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (array[i][j] != 0) {
        return false;
      }
    }
  }

  return true;
}

GameInfo_t SnakeTest::game_info() { return game_info_; }

TEST_F(SnakeTest, Constructor) {
  EXPECT_TRUE(ArrayIsEmpty(game_info().field, HEIGHT, WIDTH));
  EXPECT_TRUE(ArrayIsEmpty(game_info().next, 4, 4));
}
}  // namespace s21
