/**
 * @file snake.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SRC_BRICK_GAME_SNAKE_INCLUDE_SNAKE_H_
#define SRC_BRICK_GAME_SNAKE_INCLUDE_SNAKE_H_

#include "../../common.h"

namespace s21 {
  class Snake {
   public:
    Snake() noexcept;
   private:
    GameInfo_t game;
  };

  Snake::Snake() {
    game.field = nullptr;
    game.next = nullptr;
    game.score = 0;
    game.high_score = 0;
    game.level = 0;
    game.pause = 0;
    game.speed = 0;
  }
}

#endif  // SRC_BRICK_GAME_SNAKE_INCLUDE_SNAKE_H_
