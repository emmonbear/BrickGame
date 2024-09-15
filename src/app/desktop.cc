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

#include "gui/desktop/desktop_view.h"
#include "gui/desktop/main_window.h"
#include "snake/snake_model.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
