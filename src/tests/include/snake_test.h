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

#include "../../include/snake/snake_model.h"
#include "../include/main_test.h"

namespace s21 {
class SnakeTest : public SnakeModel {
 public:
  inline const PointVector &snake() { return snake_; }
  bool ArrayIsEmpty(int **array, int rows, int cols);
  inline void set_stage(stage_t stage) { stage_ = stage; }
  void set_snake(const PointVector &snake) { snake_ = snake; }
  void set_food(const Point &food) { food_ = food; }
  const Point &food() const { return food_; }
};
}  // namespace s21

#endif  // SRC_TESTS_INCLUDE_SNAKE_TEST_H_
