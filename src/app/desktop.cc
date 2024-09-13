/**
 * @file desktop.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <QApplication>
#include <iostream>

#include "gui/desktop/main_window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  MainWindow::GameType game_type = w.game_type();

  if (game_type == MainWindow::GameType::kSnake) {
    std::cout << "SNAKE" << std::endl;
  } else if (game_type == MainWindow::GameType::kTetris) {
    std::cout << "TETRIS" << std::endl;
  }

  return a.exec();
}
