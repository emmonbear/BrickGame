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

void allocate_2d_array(int **array, int rows, int cols) {
  array = (int **)calloc(rows, sizeof(int *));

  if (!array) {
    destroy_2d_array(array, rows, cols);
    MEM_ALLOC_ERROR
  }

  for (int i = 0; i < rows; i++) {
    array[i] = (int *)calloc(cols, sizeof(int));
    if (!array[i]) {
      destroy_2d_array(array, rows, cols);
      MEM_ALLOC_ERROR
    }
  }
}

void destroy_2d_array(int **array, int rows, int cols) {
  if (array) {
    for (int i = 0; i < rows; i++) {
      if (array[i]) {
        free(array[i]);
        array[i] = NULL;
      }
    }
    free(array);
    array = NULL;
  }
}