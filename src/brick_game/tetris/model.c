/**
 * @file fsm.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../include/tetris/model.h"

#include <locale.h>
#include <string.h>
#include <time.h>    // for time()
#include <unistd.h>  // for getcwd

#define PATH "/brick_game/tetris/high_score.txt"

static Model_t model;
static GameInfo_t game_info;

static int load_max_score();
static void write_high_score();
static int get_current_time();
static void start_stage(UserAction_t action);
static void spawn_stage();
static void moving_stage(UserAction_t action, bool hold);
static void shifting_stage(UserAction_t action, bool hold);
static void pause_stage(UserAction_t action);
static void attaching_stage();
static void game_over_stage(UserAction_t action);

void init_model() {
  setlocale(LC_ALL, "");
  srand(time(NULL));
  allocate_2d_array(&game_info.field, HEIGHT, WIDTH);
  allocate_2d_array(&game_info.next, TETROMINO_SIZE, TETROMINO_SIZE);
  allocate_2d_array(&model.figure.current_figure, TETROMINO_SIZE,
                    TETROMINO_SIZE);
  allocate_2d_array(&model.figure.rotated_figure, TETROMINO_SIZE,
                    TETROMINO_SIZE);
  init_game_info(model);
  model.figure.next_type = generate_random(model.figure.current_type);
  generate_new_figure(&model, &game_info);
}

void destroy_model() {
  destroy_2d_array(&game_info.field, HEIGHT);
  destroy_2d_array(&game_info.next, TETROMINO_SIZE);
  destroy_2d_array(&model.figure.current_figure, TETROMINO_SIZE);
  destroy_2d_array(&model.figure.rotated_figure, TETROMINO_SIZE);
}

void init_game_info() {
  game_info.score = 0;
  game_info.high_score = load_max_score();
  game_info.level = 1;
  game_info.speed = 1;
  game_info.pause = 0;
  model.figure.next_color = -1;
  model.figure.next_type = NONE;
  model.figure.current_type = NONE;
  model.figure.current_color = -1;
  model.stage = START;
  model.timer = 0;
  model.game_over = false;
}

void userInput(UserAction_t action, bool hold) {
  switch (model.stage) {
    case START:
      start_stage(action);
      break;
    case SPAWN:
      spawn_stage();
      break;
    case MOVING:
      moving_stage(action, hold);
      break;
    case SHIFTING:
      shifting_stage(action, hold);
      break;
    case PAUSE:
      pause_stage(action);
      break;
    case ATTACHING:
      attaching_stage();
      break;
    case GAME_OVER:
      game_over_stage(action);
  }
}

static int load_max_score() {
  char cwd[200];
  int max_score = 0;

  if (getcwd(cwd, sizeof(cwd))) {
    strcat(cwd, PATH);

    FILE *f = fopen(cwd, "r");

    if (f) {
      if (fscanf(f, "%d", &max_score) != 1) {
        perror("fscanf error");
      }
      fclose(f);
    }
  }

  return max_score;
}

static void write_high_score() {
  char cwd[200];

  if (getcwd(cwd, sizeof(cwd))) {
    strcat(cwd, PATH);
    FILE *f = fopen(cwd, "w");

    if (f) {
      fprintf(f, "%d", game_info.high_score);
      fclose(f);
    }
  }
}

static int get_current_time() { return (int)(clock() * 1000 / CLOCKS_PER_SEC); }

static void start_stage(UserAction_t action) {
  switch (action) {
    case Start:
      model.stage = SPAWN;
      break;
    case Terminate:
      model.stage = GAME_OVER;
      break;
    default:
      break;
  }
}

static void spawn_stage() {
  copy_next_to_current(&model, &game_info);
  put_figure(&model, &game_info);
  model.figure.next_type = generate_random(model.figure.current_type);
  generate_new_figure(&model, &game_info);
  model.stage = SHIFTING;
}

static void moving_stage(UserAction_t action, bool hold) {
  model.stage = SHIFTING;

  switch (action) {
    case Left:
      move_left(&model, &game_info);
      break;

    case Right:
      move_right(&model, &game_info);
      break;

    case Down:
      if (hold) {
        while (can_move_down(&model, &game_info)) {
          move_down(&model, &game_info);
        }
      } else if (can_move_down(&model, &game_info)) {
        move_down(&model, &game_info);
      }
      break;
    case Action:
      get_rotated_figure(&model);

      if (can_rotate(&model, &game_info)) {
        rotate_figure(&model, &game_info);
      }
      break;
    default:
      break;
  }
}

static void shifting_stage(UserAction_t action, bool hold) {
  int current_time = get_current_time();
  int wait_time = 1100 - (game_info.level * 100);

  if (can_move_down(&model, &game_info)) {
    if (current_time - model.timer >= wait_time) {
      move_down(&model, &game_info);
      model.timer = current_time;
    }
  } else {
    if ((current_time - model.timer >= wait_time)) {
      model.stage = ATTACHING;
    }
  }

  switch (action) {
    case Left:
    case Right:
    case Down:
    case Action:
      moving_stage(action, hold);
      break;
    case Terminate:
      model.stage = GAME_OVER;
      break;
    case Pause:
      model.stage = PAUSE;
      break;
    default:
      break;
  }
}

static void pause_stage(UserAction_t action) {
  switch (action) {
    case Pause:
      model.stage = SHIFTING;
      break;
    case Terminate:
      model.stage = GAME_OVER;
      break;
    default:
      break;
  }
}

static void attaching_stage() {
  check_full_lines(&game_info);
  set_start_position(&model.figure);

  if (can_put_new_line(&model, &game_info)) {
    model.stage = SPAWN;
  } else {
    model.stage = GAME_OVER;
  }
}

static void game_over_stage(UserAction_t action) {
  write_high_score();

  switch (action) {
    case Start:
      reset_field(&game_info);
      init_game_info();
      model.figure.next_type = generate_random(model.figure.current_type);
      generate_new_figure(&model, &game_info);
      model.stage = SPAWN;
      model.game_over = 0;
      break;
    case Terminate:
      model.game_over = true;
      break;
    default:
      break;
  }
}

GameInfo_t updateCurrentState() { return game_info; }

stage_t stage() { return model.stage; }

bool game_over() { return model.game_over; }
