/**
 * @file operations.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_OPERATIONS_H
#define MODULES_OPERATIONS_H

#include "../include/checks.h"
#include "./common.h"

void put_figure(Game_t *s);
void remove_figure(Game_t *s);
void move_right(Game_t *s);
void move_left(Game_t *s);
void move_down(Game_t *s);
void rotate_figure(Game_t *s);
void get_rotated_figure(Game_t *s);
void reset_field(Game_t *s);

#endif  // MODULES_OPERATIONS_H