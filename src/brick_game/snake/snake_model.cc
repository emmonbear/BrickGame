/**
 * @file snake_model.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../include/snake/snake_model.h"

#include <clocale>

namespace s21 {
SnakeModel::SnakeModel()
    : game_info_{}, snake_{}, food_{}, stage_{START}, game_over_{false} {
  InitGameInfo();
  InitSnake();
  GenerateFood();
}

SnakeModel::~SnakeModel() { destroy_2d_array(&game_info_.field, HEIGHT); };

/// @todo Установить локаль
void SnakeModel::InitGameInfo() {
  allocate_2d_array(&game_info_.field, HEIGHT, WIDTH);
  /// @todo Реализовать функцию чтения из файла с рекордом
  game_info_.level = 1;
  game_info_.speed = 1;
}

void SnakeModel::InitSnake() {
  snake_.push_back({HEIGHT / 2, WIDTH / 2});
  snake_.push_back({HEIGHT / 2, WIDTH / 2 - 1});
  snake_.push_back({HEIGHT / 2, WIDTH / 2 - 2});
}

/// @todo Сложность алгоритма можно понизить
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

void SnakeModel::userInput(UserAction_t action, bool hold) { return; }
GameInfo_t SnakeModel::updateCurrentState() { return game_info_; }

stage_t SnakeModel::stage() { return stage_; }

bool SnakeModel::game_over() { return game_over_; }

}  // namespace s21
