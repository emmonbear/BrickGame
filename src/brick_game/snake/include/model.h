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

namespace s21 {
  class SnakeModel {
   public:
    SnakeModel();
    ~SnakeModel();
    GameInfo_t info_;
   private:
  };
}

#endif  // SRC_BRICK_GAME_SNAKE_INCLUDE_MODEL_H_
