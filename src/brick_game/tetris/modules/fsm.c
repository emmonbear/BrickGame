/**
 * @file fsm.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/fsm.h"

#include <locale.h>
#include <time.h>
#include <unistd.h>

static Model_t *model = NULL;

static void start_stage(Model_t *Model_t);
static void spawn_stage(Model_t *Model_t);
static void moving_stage(Model_t *Model_t);
static void shifting_stage(Model_t *Model_t);
static void pause_stage(Model_t *Model_t);
static void attaching_stage(Model_t *Model_t);
static void game_over_stage(Model_t *Model_t);
static int get_current_time();

/**
 * @brief Initializes the game model and allocates necessary resources.
 *
 * @details
 *
 * This function sets up the game model by performing the following actions:
 * 1. Sets the locale to the user's default setting and seeds the random number
 * generator with the current time.
 * 2. Checks if the `model` pointer is valid and raises a memory allocation
 * error if not.
 * 3. Allocates memory for 2D arrays used to store the game field, the next
 * tetromino figure, the current tetromino figure, and the rotated tetromino
 * figure.
 *
 * @param model A pointer to the game model to be initialized.
 */
void init_model() {
  setlocale(LC_ALL, "");
  srand(time(NULL));
  model = (Model_t *)malloc(sizeof(Model_t));

  if (!model) {
    MEM_ALLOC_ERROR;
  }

  allocate_2d_array(&model->game_info.field, HEIGHT, WIDTH);
  allocate_2d_array(&model->game_info.next, TETROMINO_SIZE, TETROMINO_SIZE);
  allocate_2d_array(&model->figure.current_figure, TETROMINO_SIZE,
                    TETROMINO_SIZE);
  allocate_2d_array(&model->figure.rotated_figure, TETROMINO_SIZE,
                    TETROMINO_SIZE);
  reset_game_info(model);
  model->figure.next_type = generate_random(model->figure.current_type);
  generate_new_figure(model);
}

/**
 * @brief Destroys the game model and releases allocated resources.
 *
 * @details
 *
 * This function deallocates memory used by the game model. It releases the
 * resources for the game field, the next tetromino figure, and both the current
 * and rotated figures by calling the `destroy_2d_array` function for each of
 * the allocated 2D arrays. This function is typically called when the game
 * model is no longer needed, such as when the game is ending or being reset.
 *
 * @param model A pointer to the game model to be destroyed.
 */
void destroy_model() {
  if (model) {
    destroy_2d_array(&model->game_info.field, HEIGHT);
    destroy_2d_array(&model->game_info.next, TETROMINO_SIZE);
    destroy_2d_array(&model->figure.current_figure, TETROMINO_SIZE);
    destroy_2d_array(&model->figure.rotated_figure, TETROMINO_SIZE);

    free(model);
  }
}

/**
 * @brief Resets the game information to its initial state.
 *
 * @details
 *
 * This function reinitializes the game model's information to its default
 * values. It resets the score, high score, level, speed, and pause state.
 * Additionally, it clears the information related to the next and current
 * tetromino figures, including their types and colors, to prepare for a new
 * game session.
 *
 * @param model A pointer to the game model to be reset.
 */
void reset_game_info() {
  model->game_info.score = 0;
  model->game_info.high_score = load_max_score();
  model->game_info.level = 1;
  model->game_info.speed = 1;
  model->game_info.pause = 0;
  model->figure.next_color = -1;
  model->figure.next_type = NONE;
  model->figure.current_type = NONE;
  model->figure.current_color = -1;
  model->action = None;
  model->stage = START;
  model->timer = 0;
  model->game_over = false;
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
  write_high_score(&model->game_info);

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

// void userInput(UserAction_t action, bool hold) {
//   switch()
// }
