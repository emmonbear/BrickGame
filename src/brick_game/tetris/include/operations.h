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

#include <stdbool.h>

#include "../include/common_module.h"

void put_figure(singleton *s);
void remove_figure(singleton *s);
void move_right(singleton *s);
void move_left(singleton *s);
void move_down(singleton *s);
bool can_move_down(singleton *s);
bool can_move_left(singleton *s);
bool can_move_right(singleton *s);
bool is_inside_figure(singleton *s, int y, int x);
void rotate_figure(singleton *s);

#endif  // MODULES_OPERATIONS_H