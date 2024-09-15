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

#include "gui/desktop/desktop_view.h"
#include "interfaces/IModel.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  enum class GameType {
    kSnake = 0,
    kTetris,
  };

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

  void initializeButtons();
  void initializeMainWindow();
  void startGame(GameType type);
  s21::IModel *setGameModel(GameType type);
};
#endif  // SRC_INCLUDE_GUI_DESKTOP_MAIN_WINDOW_H_
