#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include <QObject>
#include <QTimer>

extern "C" {
#include "../../../brick_game/tetris/include/model.h"
#include "../../../brick_game/tetris/include/init.h"
#include "../../../brick_game/tetris/include/figures.h"
#include "../../../brick_game/tetris/include/checks.h"
#include "../../../brick_game/tetris/include/operations.h"
}

class TetrisController : public QObject
{
    Q_OBJECT
public:
    explicit TetrisController(QObject *parent = nullptr);
    ~TetrisController();

    Model_t *get_model() const;

private:
    Model_t *model_;
    

};

#endif // TETRISCONTROLLER_H
