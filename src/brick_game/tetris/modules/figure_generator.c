/**
 * @file figure_generator.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/figure_generator.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>



figure_t generate_new_figure(void) {
  figure_t figure;
  int tmp = rand() % NUM_TETROMINOS;

  figure.color = tmp;
  figure.type = tmp;

  int cells[TETROMINO_SIZE][TETROMINO_SIZE] = {0};

  switch(figure.type) {
    case TET_I:
      cells[0][0] = 1;
      cells[0][1] = 1;
      cells[0][2] = 1;
      cells[0][3] = 1;
      break;
    case TET_Z:
      cells[0][0] = 1;
      cells[0][1] = 1;
      cells[1][1] = 1;
      cells[1][2] = 1;
      break;
    case TET_S:
      cells[0][1] = 1;
      cells[0][2] = 1;
      cells[1][0] = 1;
      cells[1][1] = 1;
      break;
    case TET_T:
      cells[0][1] = 1;
      cells[1][0] = 1;
      cells[1][1] = 1;
      cells[1][2] = 1;
      break;
    case TET_L:
      cells[0][2] = 1;
      cells[1][0] = 1;
      cells[1][1] = 1;
      cells[1][2] = 1;
      break;
    case TET_J:
      cells[0][0] = 1;
      cells[1][0] = 1;
      cells[1][1] = 1;
      cells[1][2] = 1;
      break;
    case TET_O:
      cells[0][0] = 1;
      cells[0][1] = 1;
      cells[1][0] = 1;
      cells[1][1] = 1;
      break;
  }

  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for(size_t j = 0; j < TETROMINO_SIZE; j++) {
      if (cells[i][j] == 1) {
        figure.cells[i].y = 1;
        figure.cells[j].x = 1;
      }
    }
  }
  return figure;
}