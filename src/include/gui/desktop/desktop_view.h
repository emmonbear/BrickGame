/**
 * @file desktop_view.h
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

#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QWidget>

#include "controller/controller.h"
#include "gui/desktop/scoreboard.h"

namespace s21 {
class DesktopView : public QWidget {
  Q_OBJECT

 public:
  explicit DesktopView(Controller &controller, QWidget *parent = nullptr);
  void startEventLoop();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void setColor(QPainter &painter, int color);

 private:
  Controller &controller_;
  ScoreBoard *high_score_;
  ScoreBoard *score_;
  ScoreBoard *level_;

  static constexpr int kWidgetWidth = 800;
  static constexpr int kWidgetHeight = 600;
  static constexpr int kCellSize = 20;
  static constexpr int kOffset = 20;
  static constexpr int kBoardHeight = 75;
  static constexpr int kBoardWidth = 250;

  static constexpr int kFieldHeight = HEIGHT * kCellSize;
  static constexpr int kFieldWidth = WIDTH * kCellSize;
  static constexpr int kFieldX = (kWidgetWidth - kFieldWidth) / 2;
  static constexpr int kFieldY = (kWidgetHeight - kFieldHeight) / 2;

  static constexpr int kHighScoreY = kFieldY;
  static constexpr int kHighScoreX = kFieldX + kFieldWidth + kOffset;

  static constexpr int kScoreX = kHighScoreX;
  static constexpr int kScoreY = kHighScoreY + kBoardHeight + kOffset;

  static constexpr int klevelX = kScoreX;
  static constexpr int klevelY = kScoreY + kBoardHeight + kOffset;

  static constexpr int kNextX = kScoreX + 70;
  static constexpr int kNextY = klevelY + 30 + kBoardHeight + kOffset;

  void drawField(QPainter &painter, int **field);
  void handleUserInput(int key, bool hold);
  UserAction_t convertKeyToAction(int key);
  void showBoards();
  void hideBoards();
  void drawPause(QPainter &painter);
  void drawGameOver(QPainter &painter);
  void drawNext(QPainter &painter, int **next);
};
}  // namespace s21

#endif  // SRC_INCLUDE_GUI_DESKTOP_DESKTOP_VIEW_H_
