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
#include "../include/common_module.h"

void put_figure(singleton *s);
void remove_figure(singleton *s);
void move_right(singleton *s);
void move_left(singleton *s);
void move_down(singleton *s);
void rotate_figure(singleton *s);
void get_rotated_figure(singleton *s);

#endif  // MODULES_OPERATIONS_H