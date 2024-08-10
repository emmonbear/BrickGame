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
static void run_state(Controller_t *controller);
static void get_user_input(Controller_t *controller);
static void draw_game(View_t *wins, const Model_t *model, const stage_t stage);
static int get_current_time();

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

void destroy_controller(Controller_t *controller) {
  if (controller) {
    destroy_view(&controller->view);
    destroy_model(&controller->model);
    free(controller);
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
  int wait_time = 1000 - (controller->model.game_info.level * 100);

  if (wait_time < 100) {
    wait_time = 100;
  }

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
  controller->model.figure.x = 3;
  controller->model.figure.y = 0;

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

static void run_state(Controller_t *controller) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[controller->stage](controller);
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
      controller->action = -1;
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

void game_loop(Controller_t *controller) {
  int lines = LINES;
  int cols = COLS;

  reset_game_info(&controller->model);
  generate_new_figure(&controller->model);

  while (!controller->game_over) {
    resize_windows(&controller->view, &lines, &cols);
    run_state(controller);
    get_user_input(controller);
    draw_game(&controller->view, &controller->model, controller->stage);
  }
}

static int get_current_time() { return (int)(clock() * 1000 / CLOCKS_PER_SEC); }
