#ifndef TETRIS_VIEW_H
#define TETRIS_VIEW_H

#include <QWidget>
#include <QPainter>

#include "./tetris_controller.h"

class TetrisView : public QWidget
{
  Q_OBJECT
 public:
  static constexpr int kCellSize = 30;
  static constexpr int kSpace = 20;
  static constexpr int kHeight = 20;
  static constexpr int kWidth = 10;
  static constexpr int KTetrominoSize = 4;
  static constexpr int lRightWidth = 200;

  static constexpr int kFieldX = 50;
  static constexpr int kFieldY = 50;
  static constexpr int kFieldHeight = (kCellSize * kHeight) + kFieldY;
  static constexpr int kFieldWidth = (kCellSize * kWidth) + kFieldX;

  static constexpr int kHighScoreY = kFieldY;
  static constexpr int kHighScoreX = kFieldWidth + kSpace;
  static constexpr int kHighScoreHeight = 100;
  static constexpr int kHighScoreWidth = lRightWidth;

  static constexpr int kLevelY = kFieldY + kHighScoreHeight + kSpace;
  static constexpr int kLevelX = kHighScoreX;
  static constexpr int kLevelHeight = 100;
  static constexpr int kLevelWidth = lRightWidth;

  static constexpr int kScoreY = kLevelY + kLevelHeight + kSpace;
  static constexpr int kScoreX = kHighScoreX;
  static constexpr int kScoreHeight = 100;
  static constexpr int kScoreWidth = lRightWidth;

  static constexpr int kNextY = kScoreY + kScoreHeight + kSpace;
  static constexpr int kNextX = kHighScoreX;
  static constexpr int kNextHeight =  kFieldHeight - kFieldY - (kHighScoreHeight + kLevelHeight + kScoreHeight + kSpace * 3);
  static constexpr int kNextWidth = lRightWidth;

  explicit TetrisView(TetrisController *controller_, QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  QColor getColorForValue (int value) const;

 private:
  TetrisController *controller_;

  void draw_field(QPainter &painter);
  void draw_high_score(QPainter &painter);
  void draw_level(QPainter &painter);
  void draw_score(QPainter &painter);
  void draw_next(QPainter &painter);
};

#endif // TETRIS_VIEW_H
