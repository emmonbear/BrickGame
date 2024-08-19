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

#include <cstdlib>  // for crand
#include <ctime>    // for time

namespace s21 {
SnakeModel::SnakeModel() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  InitializeGame();
}

SnakeModel::~SnakeModel() { destroy_2d_array(&info_.field, HEIGHT); }

void SnakeModel::InitializeGame() {
  allocate_2d_array(&info_.field, HEIGHT, WIDTH);
  info_.next = nullptr;
  info_.high_score = load_max_score();
  info_.level = 1;
  info_.speed = 1;
  info_.score = 0;
  info_.pause = 0;
  snake_ = {{HEIGHT / 2, WIDTH / 2},
            {HEIGHT / 2, WIDTH / 2 - 1},
            {HEIGHT / 2, WIDTH / 2 - 2}};
  GenerateFood();
}

void SnakeModel::GenerateFood() {
  bool valid_position = false;

  while (!valid_position) {
    food_ = {std::rand() % HEIGHT, std::rand() % WIDTH};
    valid_position = true;

    for (const auto &iter : snake_) {
      if (iter == food_) {
        valid_position = false;
        break;
      }
    }
  }
}

void SnakeModel::UpdateField() {
  ClearField();
  PlaceSnakeOnField();
  PlaceFoodOnField();
}

void SnakeModel::ClearField() {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      info_.field[i][j] = 0;
    }
  }
}

void SnakeModel::PlaceSnakeOnField() {
  for (const auto &segment : snake_) {
    info_.field[segment.first][segment.second] = 1;
  }
}

void SnakeModel::PlaceFoodOnField() {
  info_.field[food_.first][food_.second] = 2;
}

}  // namespace s21
