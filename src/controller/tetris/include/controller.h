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

#include <time.h>

#include "../../../brick_game/tetris/include/checks.h"
#include "../../../brick_game/tetris/include/figures.h"
#include "../../../brick_game/tetris/include/init.h"
#include "../../../brick_game/tetris/include/model.h"
#include "../../../brick_game/tetris/include/operations.h"

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
} Controller_t;

typedef void (*func_ptr)(Model_t *model);

void init_controller(Controller_t *controller);
void destroy_controller(Controller_t *controller);
void run_state(Model_t *model);

#endif  // TETRIS_CONTROLLER_H
