/**
 * @file main_window.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-09-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SRC_INCLUDE_GUI_DESKTOP_MAIN_WINDOW_H_
#define SRC_INCLUDE_GUI_DESKTOP_MAIN_WINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
};
#endif  // SRC_INCLUDE_GUI_DESKTOP_MAIN_WINDOW_H_
