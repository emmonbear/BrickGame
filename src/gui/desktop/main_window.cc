/**
 * @file main_window.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "gui/desktop/main_window.h"

#include "controller/controller.h"
#include "snake/snake_model.h"
#include "wrappers/tetris_model.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  initializeMainWindow();
  initializeButtons();
}

MainWindow::~MainWindow() {}

void MainWindow::initializeMainWindow() {
  setWindowTitle("BrickGame");
  setFixedSize(800, 600);
  this->setStyleSheet("background-color: #1c1919");
}

void MainWindow::initializeButtons() {
  snakeButton = new QPushButton("Snake", this);
  tetrisButton = new QPushButton("Tetris", this);
  exitButton = new QPushButton("Exit", this);

  snakeButton->setFixedSize(400, 50);
  tetrisButton->setFixedSize(400, 50);
  exitButton->setFixedSize(400, 50);

  snakeButton->setStyleSheet(
      "background-color: #780a00; color: #1c1919; font-size: 18px; padding: "
      "10px;");
  tetrisButton->setStyleSheet(
      "background-color: #780a00; color: #1c1919; font-size: 18px; padding: "
      "10px;");
  exitButton->setStyleSheet(
      "background-color: #780a00; color: #1c1919; font-size: 18px; padding: "
      "10px;");

  QVBoxLayout *buttonLayout = new QVBoxLayout;
  buttonLayout->addWidget(snakeButton);
  buttonLayout->addWidget(tetrisButton);
  buttonLayout->addWidget(exitButton);

  buttonLayout->setAlignment(Qt::AlignCenter);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(buttonLayout);
  setCentralWidget(centralWidget);

  connect(snakeButton, &QPushButton::clicked, this,
          &MainWindow::onSnakeButtonClicked);
  connect(tetrisButton, &QPushButton::clicked, this,
          &MainWindow::onTetrisButtonClicked);
  connect(exitButton, &QPushButton::clicked, this,
          &MainWindow::onExitButtonClicked);

  snakeButton->setFocus();
}

void MainWindow::onSnakeButtonClicked() {
  startGame(GameType::kSnake);
  QApplication::quit();
}

void MainWindow::onTetrisButtonClicked() {
  startGame(GameType::kTetris);
  QApplication::quit();
}

void MainWindow::onExitButtonClicked() { QApplication::quit(); }

void MainWindow::startGame(GameType type) {
  s21::IModel *model = setGameModel(type);
  s21::Controller *controller = new s21::Controller(model);
  s21::DesktopView *view = new s21::DesktopView(*controller);

  QWidget *gameWidget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(gameWidget);
  layout->addWidget(view);
  gameWidget->setLayout(layout);
  setCentralWidget(gameWidget);

  view->setFocus();
  view->startEventLoop();
}

s21::IModel *MainWindow::setGameModel(GameType type) {
  switch (type) {
    case GameType::kSnake:
      return new s21::SnakeModel();
    case GameType::kTetris:
      return new s21::TetrisModel();
    default:
      return nullptr;
  }
}