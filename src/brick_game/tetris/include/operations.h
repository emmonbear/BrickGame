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
#include "./model.h"

void put_figure(Model_t *model);
void remove_figure(Model_t *model);
void move_right(Model_t *model);
void move_left(Model_t *model);
void move_down(Model_t *model);
void rotate_figure(Model_t *model);
void get_rotated_figure(Model_t *model);
void reset_field(Model_t *model);

#endif  // MODULES_OPERATIONS_H
