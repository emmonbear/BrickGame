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
  model->action = None;
  model->stage = START;
  model->timer = 0;
  model->game_over = false;
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
void destroy_model(Model_t *model) {
  if (model) {
    destroy_2d_array(&(model->game_info.field), HEIGHT);
    destroy_2d_array(&(model->game_info.next), TETROMINO_SIZE);
    destroy_2d_array(&(model->figure.current_figure), TETROMINO_SIZE);
    destroy_2d_array(&(model->figure.rotated_figure), TETROMINO_SIZE);
  }
}

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
  reset_game_info(model);
  model->figure.next_type = generate_random(model->figure.current_type);
  generate_new_figure(model);
}

/**
 * @brief Writes the current high score to a file.
 *
 * @details
 *
 * This function retrieves the current working directory and appends a
 * predefined path to it. It then opens a file in write mode at the resulting
 * path and writes the current high score from the game model to the file. If
 * the file is successfully opened, it writes the high score as an integer and
 * then closes the file.
 *
 * @param model A pointer to the game model containing the high score to be
 * written.
 */
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
