#ifndef TETRIS_VIEW_H
#define TETRIS_VIEW_H

#include <QWidget>
#include <QPainter>

#include "./tetris_controller.h"

class TetrisView : public QWidget
{
  Q_OBJECT
 public:
  explicit TetrisView(TetrisController *controller_, QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  QColor getColorForValue (int value) const;

 private:
  TetrisController *controller_;
};

#endif // TETRIS_VIEW_H
