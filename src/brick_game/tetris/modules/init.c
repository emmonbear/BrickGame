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

/**
 * @brief Resets the game's information to its initial state.
 *
 * @details
 *
 * This function sets the game's score, high score, level, speed, and pause flag
 * to their initial values. It also sets the next tetromino's color and type,
 * and the current tetromino's color and type to their initial values. Finally,
 * it sets the game over flag to 0.
 *
 * @param[in,out] s A pointer to the Game_t that contains the game's state
 * and information
 */
void reset_game_info(Game_t *s) {
  s->game_info.score = 0;
  s->game_info.high_score = load_max_score();
  s->game_info.level = 1;
  s->game_info.speed = 1;
  s->game_info.pause = 0;
  s->figure.next_color = -1;
  s->figure.next_type = -1;
  s->figure.current_type = -1;
  s->figure.current_color = -1;
  s->game_over = 0;
}

/**
 * @brief Deallocates memory for the game's data structures and cleans up the
 * game's state.
 *
 * @details
 *
 * This function deallocates memory for the game's data structures, including
 * the game field, the next tetromino, and the current tetromino. It also sets
 * the corresponding pointers to NULL to avoid dangling pointers. If the
 * Game_t or any of its data members are not initialized, the function does
 * nothing.
 *
 * @param[in,out] s A pointer to the Game_t that contains the game's state
 * and information
 */
void destroy_game(Game_t *s) {
  if (s) {
    destroy_2d_array(&(s->game_info.field), HEIGHT);
    destroy_2d_array(&(s->game_info.next), TETROMINO_SIZE);
    destroy_2d_array(&(s->figure.current_figure), TETROMINO_SIZE);
    destroy_2d_array(&(s->figure.rotated_figure), TETROMINO_SIZE);
  }
}

/**
 * @brief Initializes the game's state and allocates memory for the game's data
 * structures.
 *
 * @details
 *
 * This function sets the locale according to the current system settings,
 * initializes the pseudorandom number generator with the current time, and
 * allocates memory for the game's data structures, including the game field,
 * the next tetromino, and the current tetromino. If any memory allocation
 * fails, the function prints an error message and exits the program with a
 * non-zero status code.
 * @param[in,out] s A pointer to the Game_t that contains the game's state
 * and information
 */
void init_game(Game_t *s) {
  setlocale(LC_ALL, "");
  srand(time(NULL));

  if (!s) {
    MEM_ALLOC_ERROR;
  }

  allocate_2d_array(&(s->game_info.field), HEIGHT, WIDTH);
  allocate_2d_array(&(s->game_info.next), TETROMINO_SIZE, TETROMINO_SIZE);
  allocate_2d_array(&(s->figure.current_figure), TETROMINO_SIZE,
                    TETROMINO_SIZE);
  allocate_2d_array(&(s->figure.rotated_figure), TETROMINO_SIZE,
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

/**
 * @brief Writes the high score to a file.
 *
 * @details
 *
 * This function gets the current working directory and appends the file path to
 * it. It then opens the file in write mode and writes the high score to it. If
 * the file is not opened, the function does nothing.
 *
 * @param[in,out] s A pointer to the Game_t that contains the game's state
 * and information
 */
void write_high_score(Game_t *s) {
  char cwd[200];

  if (getcwd(cwd, sizeof(cwd))) {
    strcat(cwd, PATH);
    FILE *f = fopen(cwd, "w");

    if (f) {
      fprintf(f, "%d", s->game_info.high_score);
      fclose(f);
    }
  }
}