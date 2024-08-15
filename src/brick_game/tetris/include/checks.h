/**
 * @file checks.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_CHECKS_H
#define MODULES_CHECKS_H

#include "./model.h"

bool can_move_down(Model_t *model);
bool can_move_left(Model_t *model);
bool can_move_right(Model_t *model);
bool can_rotate(Model_t *model);
bool is_inside_figure(Model_t *model, int y, int x);
void check_full_lines(Model_t *model);
bool can_put_new_line(Model_t *model);

#endif  // MODULES_CHECKS_H
