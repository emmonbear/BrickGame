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

static void get_user_input(Controller_t *controller);
static void draw_game(View_t *wins, const Model_t *model, const stage_t stage);

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

  while (!controller->model.game_over) {
    resize_windows(&controller->view, &lines, &cols);
    run_state(&controller->model);
    get_user_input(controller);
    draw_game(&controller->view, &controller->model, controller->model.stage);
  }
}

static void get_user_input(Controller_t *controller) {
  switch (getch()) {
    case KEY_LEFT:
      controller->model.action = Left;
      break;
    case KEY_RIGHT:
      controller->model.action = Right;
      break;
    case KEY_DOWN:
      controller->model.action = Down;
      break;
    case ' ':
      controller->model.action = Action;
      break;
    case '\n':
      controller->model.action = Start;
      break;
    case 'p':
    case 'P':
      controller->model.action = Pause;
      break;
    case 'q':
    case 'Q':
      controller->model.action = Terminate;
      break;
    default:
      controller->model.action = None;
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
