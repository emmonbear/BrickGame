/**
 * @file scoreboard.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_GUI_DESKTOP_SCOREBOARD_H_
#define SRC_INCLUDE_GUI_DESKTOP_SCOREBOARD_H_

#include <QString>
#include <QWidget>
namespace s21 {
class ScoreBoard : public QWidget {
  Q_OBJECT

 public:
  ScoreBoard(QWidget *parent = nullptr);

  void set_info(int info);
  void set_title(const QString &title);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  int info_;
  QString title_;
};
}  // namespace s21

#endif  // SRC_INCLUDE_GUI_DESKTOP_SCOREBOARD_H_
