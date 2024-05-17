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

void reset_game_info(singleton *s) {
  s->game_info->score = 0;
  s->game_info->high_score = load_max_score();
  s->game_info->level = 1;
  s->game_info->speed = 1;
  s->game_info->pause = 0;
  s->figure.next_color = -1;
  s->figure.next_type = -1;
  s->figure.current_type = -1;
  s->figure.current_color = -1;
  s->game_over = 0;
}

void destroy_game(singleton *s) {
  if (s) {
    if (s->game_info) {
      destroy_2d_array(&(s->game_info->field), HEIGHT);
      destroy_2d_array(&(s->game_info->next), TETROMINO_SIZE);
      destroy_2d_array(&(s->figure.current_figure), TETROMINO_SIZE);
      destroy_2d_array(&(s->figure.rotated_figure), TETROMINO_SIZE);
      free(s->game_info);
      s->game_info = NULL;
    }
    if (s->action) {
      free(s->action);
      s->action = NULL;
    }
  }
}

void init_game(singleton *s) {
  setlocale(LC_ALL,
            "");  // Set the locale according to the current system settings.
                  // The locale determines language and regional settings such
                  // as date format, currency, number separators, etc.
  srand(time(NULL));  // initialize the pseudorandom number generator with the
                      // current time

  if (!s) {
    MEM_ALLOC_ERROR
  }

  s->game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  if (!s->game_info) {
    MEM_ALLOC_ERROR
  }

  allocate_2d_array(&(s->game_info->field), HEIGHT, WIDTH);
  allocate_2d_array(&(s->game_info->next), TETROMINO_SIZE, TETROMINO_SIZE);
  allocate_2d_array(&(s->figure.current_figure), TETROMINO_SIZE,
                    TETROMINO_SIZE);
  allocate_2d_array(&(s->figure.rotated_figure), TETROMINO_SIZE,
                    TETROMINO_SIZE);
  s->action = (UserAction_t *)malloc(sizeof(UserAction_t));
  if (!s->action) {
    MEM_ALLOC_ERROR
  }
}

static void allocate_2d_array(int ***array, size_t rows, size_t cols) {
  *array = (int **)calloc(rows, sizeof(int *));

  if (!(*array)) {
    MEM_ALLOC_ERROR
  }

  for (size_t i = 0; i < rows; i++) {
    (*array)[i] = (int *)calloc(cols, sizeof(int));
    if (!(*array)[i]) {
      destroy_2d_array(array, rows);
      MEM_ALLOC_ERROR
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

void write_high_score(singleton *s) {
  char cwd[200];
  if (getcwd(cwd, sizeof(cwd))) {
    strcat(cwd, PATH);
    FILE *f = fopen(cwd, "w");

    if (f) {
      fprintf(f, "%d", s->game_info->high_score);
      fclose(f);
    }
  }
}