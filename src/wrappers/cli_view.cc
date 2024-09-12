/**
 * @file cli_view.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/wrappers/cli_view.h"
#include <unistd.h>

namespace s21 {
CliView::CliView(Controller &controller) : controller_(controller) {
  init_screen();
  init_windows(&windows_);
};

CliView::~CliView() { destroy_windows(&windows_); }

void CliView::startEventLoop() {
  int lines = LINES;
  int cols = COLS;
  bool hold = false;
  UserAction_t action = None;
  UserAction_t last_key = None;
  GameInfo_t game_info;

  while (!controller_.game_over()) {
    resize_windows(&windows_, &lines, &cols);
    game_info = controller_.updateCurrentState();
    get_input(&action, &hold, &last_key);
    controller_.userInput(action, hold);
    render(&windows_, game_info, controller_.stage());
  }
}

}  // namespace s21
