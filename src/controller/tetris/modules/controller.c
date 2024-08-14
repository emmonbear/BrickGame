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

static void start_stage(Controller_t *controller);
static void spawn_stage(Controller_t *controller);
static void moving_stage(Controller_t *controller);
static void shifting_stage(Controller_t *controller);
static void pause_stage(Controller_t *controller);
static void attaching_stage(Controller_t *controller);
static void game_over_stage(Controller_t *controller);
static void get_user_input(Controller_t *controller);
static void draw_game(View_t *wins, const Model_t *model, const stage_t stage);
static int get_current_time();

/**
 * @brief Initializes a new controller structure.
 *
 * @details Allocates memory for the `Controller_t` structure, initializes
 * the model and view components, and sets default values for the action,
 * stage, timer, and game_over fields. The function will handle memory
 * allocation errors and initialize the controller to a default state.
 *
 * @return A pointer to the newly created `Controller_t` structure.
 */
Controller_t *init_controller() {
  Controller_t *controller = (Controller_t *)malloc(sizeof(Controller_t));

  if (!controller) {
    MEM_ALLOC_ERROR;
  }

  init_model(&controller->model);
  init_view(&controller->view);
  controller->action = None;
  controller->stage = START;
  controller->timer = 0;
  controller->game_over = false;

  return controller;
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
    destroy_view(&controller->view);
    destroy_model(&controller->model);
    free(controller);
  }
}

/**
 * @brief Executes the function corresponding to the current stage of the game.
 *
 * @details This function uses an array of function pointers, `state_funcs`,
 * where each function corresponds to a specific stage of the game. It calls the
 * function associated with the current stage of the game, as indicated by the
 * `stage` field in the `Controller_t` structure. The `Controller_t` pointer is
 * passed to the stage function, allowing it to modify the game's state as
 * needed.
 *
 * @param controller A pointer to the `Controller_t` structure that holds the
 *                   current state of the game.
 */
void run_state(Controller_t *controller) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[controller->stage](controller);
}

/**
 * @brief Runs the main game loop, handling game state updates and rendering.
 *
 * @details This function initializes the game state by resetting game
 * information, generating a new tetromino figure, and then enters a loop that
 * continues until the game is over. Within the loop, it performs the following
 * actions:
 * - Adjusts the window size if needed.
 * - Executes the function associated with the current game stage.
 * - Captures user input to determine the next action.
 * - Renders the current game state to the view.
 *
 * The loop will break when the `game_over` flag in the `Controller_t` structure
 * is set to true.
 *
 * @param controller A pointer to the `Controller_t` structure that manages the
 * game's state, view, and user actions.
 */
void game_loop(Controller_t *controller) {
  int lines = LINES;
  int cols = COLS;

  reset_game_info(&controller->model);
  controller->model.figure.next_type =
      generate_random(controller->model.figure.current_type);
  generate_new_figure(&controller->model);

  while (!controller->game_over) {
    resize_windows(&controller->view, &lines, &cols);
    run_state(controller);
    get_user_input(controller);
    draw_game(&controller->view, &controller->model, controller->stage);
  }
}

static void start_stage(Controller_t *controller) {
  switch (controller->action) {
    case Start:
      controller->stage = SPAWN;
      break;
    case Terminate:
      controller->stage = GAME_OVER;
      break;
    default:
      break;
  }
}

static void spawn_stage(Controller_t *controller) {
  copy_next_to_current(&controller->model);
  put_figure(&controller->model);
  controller->model.figure.next_type =
      generate_random(controller->model.figure.current_type);
  generate_new_figure(&controller->model);
  controller->stage = SHIFTING;
}

static void moving_stage(Controller_t *controller) {
  controller->stage = SHIFTING;

  switch (controller->action) {
    case Left:
      move_left(&controller->model);
      break;

    case Right:
      move_right(&controller->model);
      break;

    case Down:
      if (can_move_down(&controller->model)) {
        move_down(&controller->model);
      }
      break;
    case Action:
      get_rotated_figure(&controller->model);

      if (can_rotate(&controller->model)) {
        rotate_figure(&controller->model);
      }
      break;
    default:
      break;
  }
}

static void shifting_stage(Controller_t *controller) {
  int current_time = get_current_time();
  int wait_time = 1100 - (controller->model.game_info.level * 100);

  if (can_move_down(&controller->model)) {
    if (current_time - controller->timer >= wait_time) {
      move_down(&controller->model);
      controller->timer = current_time;
    }
  } else {
    if ((current_time - controller->timer >= wait_time)) {
      controller->stage = ATTACHING;
    }
  }

  switch (controller->action) {
    case Left:
    case Right:
    case Down:
    case Action:
      moving_stage(controller);
      break;
    case Terminate:
      controller->stage = GAME_OVER;
      break;
    case Pause:
      controller->stage = PAUSE;
      break;
    default:
      break;
  }
}

static void pause_stage(Controller_t *controller) {
  switch (controller->action) {
    case Pause:
      controller->stage = SHIFTING;
      break;
    case Terminate:
      controller->stage = GAME_OVER;
      break;
    default:
      break;
  }
}

static void attaching_stage(Controller_t *controller) {
  check_full_lines(&controller->model);
  set_figure_position(&controller->model.figure);

  if (can_put_new_line(&controller->model)) {
    controller->stage = SPAWN;
  } else {
    controller->stage = GAME_OVER;
  }
}

static void game_over_stage(Controller_t *controller) {
  write_high_score(&controller->model);

  switch (controller->action) {
    case Start:
      reset_field(&controller->model);
      reset_game_info(&controller->model);
      controller->model.figure.next_type =
          generate_random(controller->model.figure.current_type);
      generate_new_figure(&controller->model);
      controller->stage = SPAWN;
      controller->game_over = 0;
      break;
    case Terminate:
      controller->game_over = true;
      break;
    default:
      break;
  }
}

static void get_user_input(Controller_t *controller) {
  switch (getch()) {
    case KEY_LEFT:
      controller->action = Left;
      break;
    case KEY_RIGHT:
      controller->action = Right;
      break;
    case KEY_DOWN:
      controller->action = Down;
      break;
    case ' ':
      controller->action = Action;
      break;
    case '\n':
      controller->action = Start;
      break;
    case 'p':
    case 'P':
      controller->action = Pause;
      break;
    case 'q':
    case 'Q':
      controller->action = Terminate;
      break;
    default:
      controller->action = None;
      break;
  }
}

static void draw_game(View_t *wins, const Model_t *model, const stage_t stage) {
  refresh();
  switch (stage) {
    case START:
      draw_start_screen(wins->start.w);
      break;
    case PAUSE:
      draw_pause();
      break;
    case GAME_OVER:
      draw_game_over(wins->game_over.w, model->game_info.score,
                     model->game_info.high_score);
      break;
    default:
      draw_field(model->game_info.field, wins->field.w);
      draw_next(model->game_info.next, wins->next.w);
      draw_score(model->game_info.score, wins->score.w);
      draw_level(model->game_info.level, wins->level.w);
      draw_high_score(model->game_info.high_score, wins->high_score.w);
      draw_info(wins->info.w);
      break;
  }
}

static int get_current_time() { return (int)(clock() * 1000 / CLOCKS_PER_SEC); }
