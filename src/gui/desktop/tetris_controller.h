/**
 * @file tetris_controller.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Tetris controller header file
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SRC_GUI_DESKTOP_TETRIS_CONTROLLER_H_
#define SRC_GUI_DESKTOP_TETRIS_CONTROLLER_H_

#include <QObject>
#include <QTimer>

extern "C" {
  #include "../../brick_game/tetris/include/model.h"
  #include "../../brick_game/tetris/include/init.h"
  #include "../../brick_game/tetris/include/figures.h"
  #include "../../brick_game/tetris/include/checks.h"
  #include "../../brick_game/tetris/include/operations.h"
}

class TetrisController : public QObject {
  Q_OBJECT

 public:
  TetrisController(Model_t *model, QObject *parent = nullptr);
  ~TetrisController();

 private:
  Model_t *model;
};

#endif  // SRC_GUI_DESKTOP_TETRIS_CONTROLLER_H_
