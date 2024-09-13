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

#include "gui/desktop/desktop_view.h"

#include "./ui_desktop_view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  initializeMainWindow();
  initializeButtons();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initializeMainWindow() {
  setWindowTitle("BrickGame");
  resize(800, 800);
  this->setStyleSheet("background-color: #1c1919");
}

void MainWindow::initializeButtons() {
  QPushButton *snakeButton = new QPushButton("Snake", this);
  QPushButton *tetrisButton = new QPushButton("Tetris", this);
  QPushButton *exitButton = new QPushButton("Exit", this);

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

void MainWindow::onSnakeButtonClicked() {}
void MainWindow::onTetrisButtonClicked() {}
void MainWindow::onExitButtonClicked() { QApplication::quit(); }
