/**
 * @file init.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_INIT_H
#define MODULES_INIT_H

#define PATH "/brick_game/tetris/max_score.txt"

#include <stdio.h>
#include <stdlib.h>

#include "../include/common_module.h"

#define MEM_ALLOC_ERROR                         \
  fprintf(stderr, "Memory allocation error\n"); \
  exit(1);

void init_game(singleton *s);

void destroy_game(singleton *s);

void reset_game_info(singleton *s);

#endif  // MODULES_INIT_H