/**
 * @file cli.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

#include "../include/controller/controller.h"
#include "../include/snake/snake_model.h"
#include "../include/wrappers/cli_view.h"
#include "../include/wrappers/tetris_model.h"

int main() {
  s21::IModel *model = nullptr;
  int choice = 0;
  init_screen();
  show_menu(&choice);
  endwin();

  if (choice == 1) {
    model = new s21::TetrisModel();
    s21::Controller controller(model);
    s21::CliView view(controller);
    view.startEventLoop();
  } else if (choice == 0) {
    model = new s21::SnakeModel();
    s21::Controller controller(model);
    s21::CliView view(controller);
    view.startEventLoop();
  }

  return 0;
}
