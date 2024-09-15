/**
 * @file scoreboard.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "gui/desktop/scoreboard.h"

#include <QFont>
#include <QLinearGradient>
#include <QPainter>
#include <QPen>

namespace s21 {
ScoreBoard::ScoreBoard(QWidget *parent) : QWidget(parent), info_{} {
  setFixedSize(200, 75);
}

void ScoreBoard::set_info(int info) {
  info_ = info;
  update();
}

void ScoreBoard::set_title(const QString &title) {
  title_ = title;
  update();
}

void ScoreBoard::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  painter.fillRect(rect(), QColor("#1c1919"));

  QPen borderPen(QColor("#780a00"));
  borderPen.setWidth(2);
  painter.setPen(borderPen);

  painter.drawRect(rect().adjusted(1, 1, -1, -1));

  painter.setPen(QColor("#780a00"));

  painter.setFont(QFont("Arial", 14, QFont::Bold));
  painter.drawText(0, 0, width(), 30, Qt::AlignCenter, title_);

  painter.setFont(QFont("Courier", 24, QFont::Bold));
  QString scoreText = QString("%1").arg(info_);
  painter.drawText(0, 35, width(), height() - 35, Qt::AlignCenter, scoreText);
}

}  // namespace s21