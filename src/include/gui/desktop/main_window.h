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

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include "controller/controller.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  enum class GameType {
    kNone = 0,
    kSnake,
    kTetris,
  };

  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  inline GameType game_type() const { return game_type_; }

 private slots:
  void onSnakeButtonClicked();
  void onTetrisButtonClicked();
  void onExitButtonClicked();

 private:
  GameType game_type_{None};

  QPushButton *snakeButton;
  QPushButton *tetrisButton;
  QPushButton *exitButton;

  void initializeButtons();
  void initializeMainWindow();
};
#endif  // SRC_INCLUDE_GUI_DESKTOP_MAIN_WINDOW_H_
