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
  std::cout << "Выберите игру: 1 - тетрис, 2 - змейка" << std::endl;
  int choise = 0;
  std::cin >> choise;
  s21::IModel *model = nullptr;

  if (choise == 1) {
    model = new s21::TetrisModel();
    s21::Controller controller(model);
    s21::CliView view(controller);
    view.startEventLoop();
  } else if (choise == 2) {
    model = new s21::SnakeModel();
    s21::Controller controller(model);
    s21::CliView view(controller);
    view.startEventLoop();
  }

  return 0;
}