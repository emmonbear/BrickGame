/**
 * @file controller.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-08-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SRC_CONTROLLER_SNAKE_INCLUDE_CONTROLLER_H_
#define SRC_CONTROLLER_SNAKE_INCLUDE_CONTROLLER_H_

#include "../../../brick_game/snake/include/model.h"

namespace s21 {
  class SnakeController {
   public:
    SnakeController(SnakeModel *model);
    ~SnakeController() = default;
   private:
    SnakeModel *model_;
  };

}


#endif  // SRC_CONTROLLER_SNAKE_INCLUDE_CONTROLLER_H_
