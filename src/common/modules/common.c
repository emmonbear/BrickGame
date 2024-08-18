/**
 * @file common.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/common.h"

void allocate_2d_array(int ***array, size_t rows, size_t cols) {
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

void destroy_2d_array(int ***array, size_t rows) {
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

void write_high_score(GameInfo_t *info) {
  char cwd[200];

  if (getcwd(cwd, sizeof(cwd))) {
    strcat(cwd, PATH);
    FILE *f = fopen(cwd, "w");

    if (f) {
      fprintf(f, "%d", info->high_score);
      fclose(f);
    }
  }
}

int load_max_score() {
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