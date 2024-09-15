/**
 * @file desktop_view.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "gui/desktop/desktop_view.h"

#include <QCoreApplication>

namespace s21 {
DesktopView::DesktopView(Controller &controller, QWidget *)
    : controller_{controller} {
  setFixedSize(kWidgetWidth, kWidgetHeight);

  high_score_ = new ScoreBoard(this);
  high_score_->setGeometry(kHighScoreX, kHighScoreY, kBoardWidth, kBoardHeight);
  high_score_->set_title("High Score");
  high_score_->set_info(controller_.updateCurrentState().high_score);

  score_ = new ScoreBoard(this);
  score_->setGeometry(kScoreX, kScoreY, kBoardWidth, kBoardHeight);
  score_->set_title("Score");
  score_->set_info(controller_.updateCurrentState().score);

  level_ = new ScoreBoard(this);
  level_->setGeometry(klevelX, klevelY, kBoardWidth, kBoardHeight);
  level_->set_title("Level");
  level_->set_info(controller_.updateCurrentState().level);
}

void DesktopView::drawNext(QPainter &painter, int **next) {
  painter.setPen(QPen(QColor("#1c1919")));
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      setColor(painter, next[i][j]);
      painter.drawRect(kNextX + j * kCellSize, kNextY + i * kCellSize,
                       kCellSize, kCellSize);
    }
  }
}

void DesktopView::drawField(QPainter &painter, int **field) {
  painter.setPen(QPen(QColor("#780a00")));
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      setColor(painter, field[i][j]);
      painter.drawRect(kFieldX + j * kCellSize, kFieldY + i * kCellSize,
                       kCellSize, kCellSize);
    }
  }
}

void DesktopView::setColor(QPainter &painter, int color) {
  switch (color) {
    case 0:
      painter.setBrush(QBrush(QColor("#1c1919")));
      break;
    case 1:
      painter.setBrush(QBrush(Qt::red));
      break;
    case 2:
      painter.setBrush(QBrush(Qt::green));
      break;
    case 3:
      painter.setBrush(QBrush(Qt::blue));
      break;
    case 4:
      painter.setBrush(QBrush(Qt::cyan));
      break;
    case 5:
      painter.setBrush(QBrush(Qt::magenta));
      break;
    case 6:
      painter.setBrush(QBrush(Qt::yellow));
      break;
    case snake_head:
      painter.setBrush(QBrush(QColor("#ff594a")));
      break;
    case snake_body:
      painter.setBrush(QBrush(QColor("#780a00")));
      break;
    case apple:
      painter.setBrush(QBrush(QColor("#02f232")));
      break;
    default:
      painter.setBrush(QBrush(QColor("#780a00")));
      break;
  }
}

void DesktopView::startEventLoop() {
  UserAction_t action = UserAction_t::None;
  bool hold = false;
  GameInfo_t game_info;

  while (!controller_.game_over()) {
    QCoreApplication::processEvents();
    controller_.userInput(action, hold);
    game_info = controller_.updateCurrentState();

    update();
  }
}

void DesktopView::keyReleaseEvent(QKeyEvent *event) {
  handleUserInput(event->key(), false);
}

void DesktopView::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setPen(Qt::white);

  if (controller_.stage() == PAUSE) {
    drawPause(painter);
  } else if (controller_.stage() == GAME_OVER) {
    drawGameOver(painter);
  } else {
    showBoards();
    drawField(painter, controller_.updateCurrentState().field);
    drawNext(painter, controller_.updateCurrentState().next);
    high_score_->set_info(controller_.updateCurrentState().high_score);
    score_->set_info(controller_.updateCurrentState().score);
    level_->set_info(controller_.updateCurrentState().level);
  }
}

void DesktopView::drawGameOver(QPainter &painter) {
  hideBoards();

  painter.setPen(Qt::white);
  painter.setFont(QFont("Arial", 30, QFont::Bold));

  QString game_over_text = "G A M E  O V E R";
  QRect text_rect = QRect(0, 0, width(), height() / 3);
  painter.drawText(text_rect, Qt::AlignCenter, game_over_text);

  int high_score = controller_.updateCurrentState().high_score;
  QString high_score_text = QString("High Score: %1").arg(high_score);
  painter.setFont(QFont("Arial", 20, QFont::Bold));
  QRect high_score_rect = QRect(0, height() / 3, width(), height() / 6);
  painter.drawText(high_score_rect, Qt::AlignCenter, high_score_text);

  int score = controller_.updateCurrentState().score;
  QString score_text = QString("Score: %1").arg(score);
  QRect score_rect = QRect(0, height() / 2, width(), height() / 6);
  painter.drawText(score_rect, Qt::AlignCenter, score_text);
}

void DesktopView::drawPause(QPainter &painter) {
  hideBoards();
  painter.setPen(Qt::white);
  painter.setFont(QFont("Arial", 30, QFont::Bold));

  QString pause_text = "P A U S E";
  QRect text_rect = QRect(0, 0, width(), height());
  painter.drawText(text_rect, Qt::AlignCenter, pause_text);
}

void DesktopView::hideBoards() {
  if (high_score_->isVisible()) {
    high_score_->hide();
  }

  if (score_->isVisible()) {
    score_->hide();
  }

  if (level_->isVisible()) {
    level_->hide();
  }
}

void DesktopView::showBoards() {
  if (!high_score_->isVisible()) {
    high_score_->show();
  }

  if (!score_->isVisible()) {
    score_->show();
  }

  if (!level_->isVisible()) {
    level_->show();
  }
}

void DesktopView::handleUserInput(int key, bool hold) {
  UserAction_t action = convertKeyToAction(key);
  controller_.userInput(action, hold);
}

UserAction_t DesktopView::convertKeyToAction(int key) {
  switch (key) {
    case Qt::Key_Left:
      return UserAction_t::Left;
    case Qt::Key_Right:
      return UserAction_t::Right;
    case Qt::Key_Up:
      return UserAction_t::Up;
    case Qt::Key_Down:
      return UserAction_t::Down;
    case Qt::Key_Space:
      return UserAction_t::Action;
    case Qt::Key_P:
      return UserAction_t::Pause;
    case Qt::Key_Enter:
      return UserAction_t::Start;
    case Qt::Key_Q:
      return UserAction_t::Terminate;
    default:
      return UserAction_t::None;
  }
}

}  // namespace s21
