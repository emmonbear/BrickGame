/**
 * @file model.cpp
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-08-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/model.h"

namespace s21 {
  SnakeModel::SnakeModel() {
    allocate_2d_array(&info_.field, HEIGHT, WIDTH);
    info_.next = nullptr;
    info_.high_score = load_max_score();
    info_.level = 1;
    info_.speed = 1;
    info_.score = 0;
    info_.pause = 0;
  }

  SnakeModel::~SnakeModel() {
    destroy_2d_array(&info_.field, HEIGHT);
  }
}