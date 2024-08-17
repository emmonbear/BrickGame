/**
 * @file controller.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/controller.h"

#include <time.h>

static void start_stage(Model_t *Model_t);
static void spawn_stage(Model_t *Model_t);
static void moving_stage(Model_t *Model_t);
static void shifting_stage(Model_t *Model_t);
static void pause_stage(Model_t *Model_t);
static void attaching_stage(Model_t *Model_t);
static void game_over_stage(Model_t *Model_t);
static int get_current_time();

/**
 * @brief Executes the function corresponding to the current stage of the game.
 *
 * @details This function uses an array of function pointers, `state_funcs`,
 * where each function corresponds to a specific stage of the game. It calls the
 * function associated with the current stage of the game, as indicated by the
 * `stage` field in the `Model_t` structure. The `Model_t` pointer is
 * passed to the stage function, allowing it to modify the game's state as
 * needed.
 *
 * @param model A pointer to the `Model_t` structure that holds the
 *                   current state of the game.
 */
void run_state(Model_t *model) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[model->stage](model);
}

static void start_stage(Model_t *model) {
  switch (model->action) {
    case Start:
      model->stage = SPAWN;
      break;
    case Terminate:
      model->stage = GAME_OVER;
      break;
    default:
      break;
  }
}

static void spawn_stage(Model_t *model) {
  copy_next_to_current(model);
  put_figure(model);
  model->figure.next_type = generate_random(model->figure.current_type);
  generate_new_figure(model);
  model->stage = SHIFTING;
}

static void moving_stage(Model_t *model) {
  model->stage = SHIFTING;

  switch (model->action) {
    case Left:
      move_left(model);
      break;

    case Right:
      move_right(model);
      break;

    case Down:
      if (can_move_down(model)) {
        move_down(model);
      }
      break;
    case Action:
      get_rotated_figure(model);

      if (can_rotate(model)) {
        rotate_figure(model);
      }
      break;
    default:
      break;
  }
}

static void shifting_stage(Model_t *model) {
  int current_time = get_current_time();
  int wait_time = 1100 - (model->game_info.level * 100);

  if (can_move_down(model)) {
    if (current_time - model->timer >= wait_time) {
      move_down(model);
      model->timer = current_time;
    }
  } else {
    if ((current_time - model->timer >= wait_time)) {
      model->stage = ATTACHING;
    }
  }

  switch (model->action) {
    case Left:
    case Right:
    case Down:
    case Action:
      moving_stage(model);
      break;
    case Terminate:
      model->stage = GAME_OVER;
      break;
    case Pause:
      model->stage = PAUSE;
      break;
    default:
      break;
  }
}

static void pause_stage(Model_t *model) {
  switch (model->action) {
    case Pause:
      model->stage = SHIFTING;
      break;
    case Terminate:
      model->stage = GAME_OVER;
      break;
    default:
      break;
  }
}

static void attaching_stage(Model_t *model) {
  check_full_lines(model);
  set_figure_position(&model->figure);

  if (can_put_new_line(model)) {
    model->stage = SPAWN;
  } else {
    model->stage = GAME_OVER;
  }
}

static void game_over_stage(Model_t *model) {
  write_high_score(model);

  switch (model->action) {
    case Start:
      reset_field(model);
      reset_game_info(model);
      model->figure.next_type = generate_random(model->figure.current_type);
      generate_new_figure(model);
      model->stage = SPAWN;
      model->game_over = 0;
      break;
    case Terminate:
      model->game_over = true;
      break;
    default:
      break;
  }
}

static int get_current_time() { return (int)(clock() * 1000 / CLOCKS_PER_SEC); }
/**
 * @brief Initializes a new controller structure.
 *
 * @details Allocates memory for the `Controller_t` structure, initializes
 * the model and view components, and sets default values for the action,
 * stage, timer, and game_over fields. The function will handle memory
 * allocation errors and initialize the controller to a default state.
 *
 * @param controller pointer to the newly created `Controller_t` structure.
 */
void init_controller(Controller_t *controller) {
  if (!controller) {
    MEM_ALLOC_ERROR;
  }

  init_model(&controller->model);
}

/**
 * @brief Frees the resources allocated for the controller.
 *
 * @details This function deallocates the memory used by the `Controller_t`
 * structure, including its model and view components. It first destroys the
 * view and model associated with the controller before freeing the controller's
 * own memory. The function handles the case where the controller pointer is
 * NULL.
 *
 * @param controller A pointer to the `Controller_t` structure to be destroyed.
 */
void destroy_controller(Controller_t *controller) {
  if (controller) {
    destroy_model(&controller->model);
  }
}
