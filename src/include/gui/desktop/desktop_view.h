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

#ifndef SRC_INCLUDE_GUI_DESKTOP_DESKTOP_VIEW_H_
#define SRC_INCLUDE_GUI_DESKTOP_DESKTOP_VIEW_H_

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include "controller/controller.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void onSnakeButtonClicked();
  void onTetrisButtonClicked();
  void onExitButtonClicked();

 private:
  QPushButton *snakeButton;
  QPushButton *tetrisButton;
  QPushButton *exitButton;

  s21::Controller *controller_ = nullptr;

  void initializeButtons();
  void initializeMainWindow();
};
#endif  // SRC_INCLUDE_GUI_DESKTOP_DESKTOP_VIEW_H_
