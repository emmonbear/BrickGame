#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QApplication>

class TetrisView;

extern "C" {
#include "../../../brick_game/tetris/include/model.h"
#include "../../../brick_game/tetris/include/init.h"
#include "../../../brick_game/tetris/include/figures.h"
#include "../../../brick_game/tetris/include/checks.h"
#include "../../../brick_game/tetris/include/operations.h"
#include "../../../brick_game/tetris/include/fsm.h"
}

class TetrisController : public QObject
{
    Q_OBJECT
public:
    explicit TetrisController(QObject *parent = nullptr);
    ~TetrisController();

    Model_t *get_model() const;
    void gameLoop();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void action();
    void terminate();
    void start();
    void pause();
    void none();
private:
    Model_t *model_;
    TetrisView *view_;
};

#endif // TETRISCONTROLLER_H
