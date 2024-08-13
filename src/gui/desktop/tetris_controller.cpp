/**
 * @file tetris_controller.cpp
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Tetris controller
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./tetris_controller.h"

TetrisController::TetrisController(Model_t *model, QObject *parent) : QObject(parent), model(model) {
    init_model(model);
}

TetrisController::~TetrisController() {
    destroy_model(model);
}
