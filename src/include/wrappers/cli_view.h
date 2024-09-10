/**
 * @file cli_view.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_WRAPPERS_CLI_VIEW_H_
#define SRC_INCLUDE_WRAPPERS_CLI_VIEW_H_

extern "C" {
#include "../gui/cli/render.h"
}

#include "../controller/controller.h"

namespace s21 {
class CliView {
 public:
  CliView(Controller &controller);
  ~CliView();
  void startEventLoop();

 private:
  Controller &controller_;
  Windows_t windows_;
};
}  // namespace s21

#endif  // SRC_INCLUDE_WRAPPERS_CLI_VIEW_H_
