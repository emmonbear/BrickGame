/**
 * @file init.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/init.h"

#include <locale.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static int load_max_score();
static void allocate_2d_array(int ***array, size_t rows, size_t cols);
static void destroy_2d_array(int ***array, size_t rows);

void reset_game_info(Model_t *model) {
  model->game_info.score = 0;
  model->game_info.high_score = load_max_score();
  model->game_info.level = 1;
  model->game_info.speed = 1;
  model->game_info.pause = 0;
  model->figure.next_color = -1;
  model->figure.next_type = NONE;
  model->figure.current_type = NONE;
  model->figure.current_color = -1;
}

void destroy_model(Model_t *model) {
  if (model) {
    destroy_2d_array(&(model->game_info.field), HEIGHT);
    destroy_2d_array(&(model->game_info.next), TETROMINO_SIZE);
    destroy_2d_array(&(model->figure.current_figure), TETROMINO_SIZE);
    destroy_2d_array(&(model->figure.rotated_figure), TETROMINO_SIZE);
  }
}

void init_model(Model_t *model) {
  setlocale(LC_ALL, "");
  srand(time(NULL));

  if (!model) {
    MEM_ALLOC_ERROR;
  }

  allocate_2d_array(&(model->game_info.field), HEIGHT, WIDTH);
  allocate_2d_array(&(model->game_info.next), TETROMINO_SIZE, TETROMINO_SIZE);
  allocate_2d_array(&(model->figure.current_figure), TETROMINO_SIZE,
                    TETROMINO_SIZE);
  allocate_2d_array(&(model->figure.rotated_figure), TETROMINO_SIZE,
                    TETROMINO_SIZE);
}

static void allocate_2d_array(int ***array, size_t rows, size_t cols) {
  *array = (int **)calloc(rows, sizeof(int *));

  if (!(*array)) {
    MEM_ALLOC_ERROR;
  }

  for (size_t i = 0; i < rows; i++) {
    (*array)[i] = (int *)calloc(cols, sizeof(int));
    if (!(*array)[i]) {
      destroy_2d_array(array, rows);
      MEM_ALLOC_ERROR;
    }
  }
}

static void destroy_2d_array(int ***array, size_t rows) {
  if (*array) {
    for (size_t i = 0; i < rows; i++) {
      if ((*array)[i]) {
        free((*array)[i]);
        (*array)[i] = NULL;
      }
    }
    free(*array);
    *array = NULL;
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

void write_high_score(Model_t *model) {
  char cwd[200];

  if (getcwd(cwd, sizeof(cwd))) {
    strcat(cwd, PATH);
    FILE *f = fopen(cwd, "w");

    if (f) {
      fprintf(f, "%d", model->game_info.high_score);
      fclose(f);
    }
  }
}
