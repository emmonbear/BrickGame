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
    : game_info_{},
      snake_{},
      food_{},
      stage_{START},
      game_over_{false},
      current_direction_{Direction::kRight},
      last_move_time_(std::chrono::steady_clock::now()),
      move_delay_{700} {
  InitGameInfo();
  InitSnake();
}

SnakeModel::~SnakeModel() {
  destroy_2d_array(&game_info_.field, HEIGHT);
  destroy_2d_array(&game_info_.next, 4);
};

/// @todo Установить локаль
void SnakeModel::InitGameInfo() {
  allocate_2d_array(&game_info_.field, HEIGHT, WIDTH);
  /// @todo Приходится Инициализировать поле, дабы не было сеги
  allocate_2d_array(&game_info_.next, 4, 4);
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

void SnakeModel::userInput(UserAction_t action, bool hold) {
  switch (stage_) {
    case START:
      start_stage(action);
      break;
    case SPAWN:
      spawn_stage();
      break;
    case MOVING:
      moving_stage(action);
      break;
    case SHIFTING:
      shifting_stage(action);
      break;
    // case PAUSE:
    //   pause_stage(action);
    //   break;
    case ATTACHING:
      attaching_stage();
      break;
    case GAME_OVER:
      game_over_stage(action);
      break;
  }
}

GameInfo_t SnakeModel::updateCurrentState() { return game_info_; }

stage_t SnakeModel::stage() { return stage_; }

bool SnakeModel::game_over() { return game_over_; }

void SnakeModel::PlaceFoodOnField() {
  game_info_.field[food_.first][food_.second] = red;
}

void SnakeModel::PlaceSnakeOnField() {
  game_info_.field[snake_.front().first][snake_.front().second] = blue;

  for (size_t i = 1; i < snake_.size(); ++i) {
    game_info_.field[snake_[i].first][snake_[i].second] = yellow;
  }
}

void SnakeModel::set_direction(Direction new_direction) {
  if ((static_cast<int>(current_direction_) + 2) % 4 !=
      static_cast<int>(new_direction)) {
    current_direction_ = new_direction;
  }
}

void SnakeModel::ClearField() {
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      game_info_.field[i][j] = 0;
    }
  }
}

bool SnakeModel::IsSnakeEat(const Point &head) const { return head == food_; }

bool SnakeModel::IsTimeToMove() {
  auto now = SteadyClock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                               last_move_time_)
             .count() >= move_delay_;
}
bool SnakeModel::CheckCollision(const Point &new_head) const {
  return IsOutOfBounds(new_head) || IsSelfCollision(new_head);
}

bool SnakeModel::IsOutOfBounds(const Point &head) const {
  return (head.first < 0 || head.first >= HEIGHT || head.second < 0 ||
          head.second >= WIDTH);
}

bool SnakeModel::IsSelfCollision(const Point &head) const {
  for (size_t i = 0; i < snake_.size(); ++i) {
    if (head == snake_[i]) {
      return true;
    }
  }

  return false;
}

void SnakeModel::start_stage(UserAction_t action) {
  switch (action) {
    case Start:
      stage_ = SPAWN;
      break;
    case Terminate:
      stage_ = GAME_OVER;
      break;
    default:
      break;
  }
}

void SnakeModel::spawn_stage() {
  GenerateFood();
  PlaceSnakeOnField();
  PlaceFoodOnField();
  stage_ = SHIFTING;
}

void SnakeModel::HandleUserDirection(UserAction_t action) {
  switch (action) {
    case Left:
      set_direction(Direction::kLeft);
      break;
    case Right:
      set_direction(Direction::kRight);
      break;
    case Down:
      set_direction(Direction::kDown);
      break;
    case Up:
      set_direction(Direction::kUp);
      break;
    case Action:
      break;
    default:
      break;
  }
}

void SnakeModel::moving_stage(UserAction_t action) {
  Point new_head = snake_.front();
  // HandleUserDirection(action);
  switch (current_direction_) {
    case Direction::kUp:
      new_head.first -= 1;
      break;
    case Direction::kDown:
      new_head.first += 1;
      break;
    case Direction::kLeft:
      new_head.second -= 1;
      break;
    case Direction::kRight:
      new_head.second += 1;
      break;
  }

  if (CheckCollision(new_head)) {
    stage_ = GAME_OVER;
  } else {
    snake_.insert(snake_.begin(), new_head);

    if (IsSnakeEat(new_head)) {
      // stage_ = ATTACHING;
    } else {
      snake_.pop_back();
      stage_ = SHIFTING;
    }
  }
}

void SnakeModel::UpdateField() {
  ClearField();
  PlaceFoodOnField();
  PlaceSnakeOnField();
}

void SnakeModel::shifting_stage(UserAction_t action) {
  HandleUserDirection(action);
  if (IsTimeToMove()) {
    moving_stage(action);
    last_move_time_ = SteadyClock::now();
  }

  switch (action) {
    case Terminate:
      stage_ = GAME_OVER;
      break;
    case Pause:
      stage_ = PAUSE;
      break;
    default:
      break;
  }
  UpdateField();
}

void SnakeModel::attaching_stage() { return; }

void SnakeModel::game_over_stage(UserAction_t action) { game_over_ = true; }

}  // namespace s21
