/**
 * @file controller.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TETRIS_CONTROLLER_H
#define TETRIS_CONTROLLER_H

// #include "../../../brick_game/tetris/include/checks.h"
// #include "../../../brick_game/tetris/include/figures.h"
// #include "../../../brick_game/tetris/include/init.h"
// #include "../../../brick_game/tetris/include/model.h"
#include "../../../brick_game/tetris/include/fsm.h"
#include "../../../gui/cli/include/field_view.h"
#include "../../../gui/cli/include/init_view.h"
#include "../../../gui/cli/include/view.h"

/**
 * @brief The controller structure for managing game state and user
 * interactions.
 *
 * @details This structure integrates the game model, view, and user actions to
 * control the game flow and update the game state. It also handles the game
 * stage and timing, as well as tracking whether the game has ended.
 */
typedef struct {
  Model_t model;  ///< The game model, containing game data and logic
  View_t view;    ///< The game view, responsible for rendering the game state
} Controller_t;

Controller_t *init_controller();
void game_loop(Controller_t *controller);
void destroy_controller(Controller_t *controller);

#endif  // TETRIS_CONTROLLER_H
