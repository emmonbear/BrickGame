/**
 * @file IModel.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_INTERFACES_IMODEL_H_
#define SRC_INCLUDE_INTERFACES_IMODEL_H_

#include "../common/game_info.h"

namespace s21 {
class IModel {
 public:
  virtual ~IModel() = default;
  virtual void userInput(UserAction_t action, bool hold) = 0;
  virtual GameInfo_t updateCurrentState() = 0;
  virtual stage_t stage() = 0;
  virtual bool game_over() = 0;
};
}  // namespace s21

#endif  // SRC_INCLUDE_INTERFACES_IMODEL_H_
