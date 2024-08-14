#include "tetris_controller.h"

TetrisController::TetrisController(QObject *parent)
    : QObject{parent}, model_(new Model_t)
{
    init_model(model_);
    reset_game_info(model_);
}

TetrisController::~TetrisController() {
    destroy_model(model_);
    delete model_;
}

Model_t *TetrisController::get_model() const {
    return model_;
}
