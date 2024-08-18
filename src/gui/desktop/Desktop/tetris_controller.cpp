#include "tetris_controller.h"

TetrisController::TetrisController(QObject *parent)
    : QObject{parent}, model_(new Model_t)
{
    init_model(model_);
}

TetrisController::~TetrisController() {
    destroy_model(model_);
    delete model_;
}

Model_t *TetrisController::get_model() const {
    return model_;
}

void TetrisController::moveLeft() {
    model_->action = UserAction_t::Left;
}

void TetrisController::moveRight() {
    model_->action = UserAction_t::Right;
}

void TetrisController::moveUp() {
    model_->action = UserAction_t::Up;
}

void TetrisController::moveDown() {
    model_->action = UserAction_t::Down;
}

void TetrisController::action() {
    model_->action = UserAction_t::Action;
}

void TetrisController::terminate() {
    model_->action = UserAction_t::Terminate;
}

void TetrisController::start() {
    model_->action = UserAction_t::Start;
}

void TetrisController::pause() {
    model_->action = UserAction_t::Pause;
}

void TetrisController::none() {
    model_->action = UserAction_t::None;
}

void TetrisController::gameLoop() {
    while(!model_->game_over) {
        run_state(model_);
        QApplication::processEvents();
        view_update();
    }
}
