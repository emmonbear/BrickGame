/**
 * @file snake_model.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_SNAKE_SNAKE_MODEL_H_
#define SRC_INCLUDE_SNAKE_SNAKE_MODEL_H_

extern "C" {
#include "../../include/common/common.h"
#include "../../include/common/game_info.h"
}

#include <chrono>
#include <utility>
#include <vector>
#include <queue>
#include <fstream>

#include "../interfaces/IModel.h"


namespace s21 {

class SnakeModel : public IModel {
 public:
  using Point = std::pair<int, int>;
  using PointVector = std::vector<Point>;
  using SteadyClock = std::chrono::steady_clock;
  using Time = std::chrono::time_point<SteadyClock>;

  enum class Direction {
    kUp = 0,
    kLeft,
    kDown,
    kRight,
  };

  SnakeModel();
  ~SnakeModel();

  void GenerateFood();
  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;
  stage_t stage() override;
  bool game_over() override;

 protected:
  const std::string kHighScoreFileName = "brick_game/snake/high_score.txt";

  GameInfo_t game_info_;
  PointVector snake_;
  Point food_;
  stage_t stage_;
  bool game_over_;
  std::queue<Direction> direction_;
  Time last_move_time_;
  int move_delay_;

  void InitGameInfo();
  void InitSnake();
  void PlaceFoodOnField();
  void PlaceSnakeOnField();
  void ClearField();
  bool CheckCollision(const Point &new_head) const;
  void HandleUserDirection(UserAction_t action);
  bool IsOutOfBounds(const Point &head) const;
  bool IsSelfCollision(const Point &head) const;
  bool IsTimeToMove() const;
  bool IsNewLevel() const;
  bool IsSnakeEat(const Point &head) const;
  bool IsNewRecord() const;
  void UpdateField();
  void LoadHighScore();
  void SaveHighScore() const;
  void set_direction(Direction new_direction);
  void start_stage(UserAction_t action);
  void spawn_stage();
  void moving_stage(UserAction_t action);
  void shifting_stage(UserAction_t action);
  // void pause_stage(UserAction_t action);
  void attaching_stage();
  void game_over_stage(UserAction_t action);
};
}  // namespace s21

#endif  // SRC_INCLUDE_SNAKE_SNAKE_MODEL_H_
